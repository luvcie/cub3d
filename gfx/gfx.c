// Window, input, drawing and XPM loading on top of SDL3.
// The frame is a 0x00RRGGBB buffer, shown once per loop iteration.

#include "gfx.h"
#include <SDL3/SDL.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "font8x8_basic.h"
#ifdef __EMSCRIPTEN__
# include <emscripten.h>
#endif

#define GLYPH_SIZE 8
#define XPM_MAX_CPP 2

struct s_gfx
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	t_image			*frame;
	t_gfx_hooks		hooks;
};

typedef struct s_xpm_color
{
	char		key[XPM_MAX_CPP];
	uint32_t	color;
}	t_xpm_color;

// takes: gfx after a failed step of gfx_init
// returns: NULL, after printing the SDL error and freeing gfx
static t_gfx	*init_failed(t_gfx *gfx)
{
	fprintf(stderr, "gfx_init failed: %s\n", SDL_GetError());
	gfx_quit(gfx);
	return (NULL);
}

// takes: gfx with a renderer, new size, output texture and frame
// returns: 1 on success, 0 on failure (nothing is left allocated)
static bool	make_buffers(t_gfx *gfx, int w, int h, SDL_Texture **tex,
		t_image **img)
{
	*tex = SDL_CreateTexture(gfx->renderer, SDL_PIXELFORMAT_XRGB8888,
			SDL_TEXTUREACCESS_STREAMING, w, h);
	if (!*tex)
		return (false);
	*img = gfx_new_image(w, h);
	if (!*img)
	{
		SDL_DestroyTexture(*tex);
		*tex = NULL;
		return (false);
	}
	return (true);
}

// takes: gfx
// mutates: drains the SDL event queue and dispatches to the hooks
static void	poll_events(t_gfx *gfx)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
#ifdef __EMSCRIPTEN__
		// browsers use ESC to leave fullscreen/pointer lock, not the game
		if ((e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP)
			&& e.key.key == SDLK_ESCAPE)
			continue ;
#endif
		if (e.type == SDL_EVENT_KEY_DOWN && !e.key.repeat
			&& gfx->hooks.key_press)
			gfx->hooks.key_press((int)e.key.key, gfx->hooks.param);
		else if (e.type == SDL_EVENT_KEY_UP && gfx->hooks.key_release)
			gfx->hooks.key_release((int)e.key.key, gfx->hooks.param);
		else if (e.type == SDL_EVENT_MOUSE_MOTION && gfx->hooks.mouse_move)
			gfx->hooks.mouse_move((int)e.motion.x, (int)e.motion.y,
				gfx->hooks.param);
		else if ((e.type == SDL_EVENT_QUIT
				|| e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
			&& gfx->hooks.close)
			gfx->hooks.close(gfx->hooks.param);
	}
}

// takes: gfx
// mutates: uploads the current frame and shows it
// a frame hook may resize: read the frame and texture here, not cached
static void	present(t_gfx *gfx)
{
	SDL_UpdateTexture(gfx->texture, NULL, gfx->frame->pixels,
		gfx->frame->w * (int)sizeof(uint32_t));
	SDL_RenderClear(gfx->renderer);
	SDL_RenderTexture(gfx->renderer, gfx->texture, NULL, NULL);
	SDL_RenderPresent(gfx->renderer);
}

// one loop iteration: events, frame hook, present
// takes: gfx as void pointer (for emscripten_set_main_loop_arg)
static void	step(void *param)
{
	t_gfx	*gfx;

	gfx = param;
	poll_events(gfx);
	if (gfx->hooks.frame)
		gfx->hooks.frame(gfx->hooks.param);
	present(gfx);
}

t_gfx	*gfx_init(const char *title, int w, int h)
{
	t_gfx	*gfx;

	gfx = calloc(1, sizeof(t_gfx));
	if (!gfx)
		return (NULL);
	if (!SDL_Init(SDL_INIT_VIDEO))
		return (init_failed(gfx));
	if (w <= 0 || h <= 0)
		gfx_screen_size(gfx, &w, &h);
	gfx->window = SDL_CreateWindow(title, w, h, 0);
	if (!gfx->window)
		return (init_failed(gfx));
	SDL_SetWindowPosition(gfx->window, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED);
	gfx->renderer = SDL_CreateRenderer(gfx->window, NULL);
	if (!gfx->renderer)
		return (init_failed(gfx));
	SDL_SetRenderVSync(gfx->renderer, 1);
	if (!make_buffers(gfx, w, h, &gfx->texture, &gfx->frame))
		return (init_failed(gfx));
	return (gfx);
}

void	gfx_quit(t_gfx *gfx)
{
	if (!gfx)
		return ;
	if (gfx->texture)
		SDL_DestroyTexture(gfx->texture);
	if (gfx->renderer)
		SDL_DestroyRenderer(gfx->renderer);
	if (gfx->window)
		SDL_DestroyWindow(gfx->window);
	gfx_free_image(gfx->frame);
	SDL_Quit();
	free(gfx);
}

// takes: gfx, new size
// returns: 1 on success; on failure the window and frame stay as they were
// mutates: replaces the frame, so the old pointer from gfx_frame is invalid
bool	gfx_resize(t_gfx *gfx, int w, int h)
{
	SDL_Texture	*tex;
	t_image		*img;

	if (!make_buffers(gfx, w, h, &tex, &img))
		return (false);
	SDL_DestroyTexture(gfx->texture);
	gfx_free_image(gfx->frame);
	gfx->texture = tex;
	gfx->frame = img;
	SDL_SetWindowSize(gfx->window, w, h);
	SDL_SetWindowPosition(gfx->window, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED);
	return (true);
}

// gfx is unused: the size comes from the display, not the window
void	gfx_screen_size(t_gfx *gfx, int *w, int *h)
{
	(void)gfx;
#ifdef __EMSCRIPTEN__
	*w = 1280;
	*h = 720;
#else
	const SDL_DisplayMode	*mode;

	*w = 1280;
	*h = 720;
	mode = SDL_GetDesktopDisplayMode(SDL_GetPrimaryDisplay());
	if (mode)
	{
		*w = mode->w;
		*h = mode->h;
	}
#endif
}

t_image	*gfx_frame(t_gfx *gfx)
{
	return (gfx->frame);
}

// takes: gfx, hooks (copied, so the caller's struct may be a temporary)
// mutates: runs the loop, on native it does not return
void	gfx_run(t_gfx *gfx, const t_gfx_hooks *hooks)
{
	gfx->hooks = *hooks;
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(step, gfx, 0, 1);
#else
	while (1)
		step(gfx);
#endif
}

t_image	*gfx_new_image(int w, int h)
{
	t_image	*img;

	if (w <= 0 || h <= 0)
		return (NULL);
	img = malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->pixels = calloc((size_t)w * h, sizeof(uint32_t));
	if (!img->pixels)
	{
		free(img);
		return (NULL);
	}
	img->w = w;
	img->h = h;
	return (img);
}

// takes: path
// returns: malloc'd file contents (NUL terminated), size in *len, or NULL
static char	*read_file(const char *path, long *len)
{
	FILE	*f;
	char	*buf;

	f = fopen(path, "rb");
	if (!f)
		return (NULL);
	if (fseek(f, 0, SEEK_END) != 0 || (*len = ftell(f)) < 0
		|| fseek(f, 0, SEEK_SET) != 0)
		return (fclose(f), NULL);
	buf = malloc(*len + 1);
	if (!buf)
		return (fclose(f), NULL);
	if (fread(buf, 1, (size_t)*len, f) != (size_t)*len)
	{
		free(buf);
		fclose(f);
		return (NULL);
	}
	buf[*len] = '\0';
	fclose(f);
	return (buf);
}

// takes: file buffer, its length, read cursor
// returns: malloc'd copy of the next "..." literal, skipping comments and
//          other text; NULL at end of input
static char	*next_literal(char *buf, long len, long *pos)
{
	long	start;
	long	end;
	char	*lit;

	while (*pos < len)
	{
		if (buf[*pos] == '/' && *pos + 1 < len && buf[*pos + 1] == '*')
		{
			*pos += 2;
			while (*pos + 1 < len && !(buf[*pos] == '*' && buf[*pos + 1] == '/'))
				(*pos)++;
			*pos += 2;
		}
		else if (buf[*pos] == '"')
		{
			(*pos)++;
			start = *pos;
			while (*pos < len && buf[*pos] != '"')
				(*pos)++;
			if (*pos >= len)
				return (NULL);
			end = *pos;
			(*pos)++;
			lit = malloc(end - start + 1);
			if (!lit)
				return (NULL);
			memcpy(lit, buf + start, end - start);
			lit[end - start] = '\0';
			return (lit);
		}
		else
			(*pos)++;
	}
	return (NULL);
}

// takes: header string "cols rows ncolors cpp"
// mutates: sets the four values, returns 1 if valid and supported
static int	parse_header(char *s, int *cols, int *rows, int *ncolors, int *cpp)
{
	if (sscanf(s, "%d %d %d %d", cols, rows, ncolors, cpp) != 4)
		return (0);
	return (*cols > 0 && *rows > 0 && *ncolors > 0
		&& *cpp >= 1 && *cpp <= XPM_MAX_CPP);
}

// takes: color line such as "X c #5B5B50" or "  c None", cpp, entry
// mutates: fills entry key and color, returns 1 on success
static int	parse_color_line(char *s, int cpp, t_xpm_color *ent)
{
	char	*p;
	char	*end;
	int		i;

	i = -1;
	while (++i < cpp)
	{
		if (s[i] == '\0')
			return (0);
		ent->key[i] = s[i];
	}
	p = s + cpp;
	if (!isspace((unsigned char)*p))
		return (0);
	while (isspace((unsigned char)*p))
		p++;
	if (p[0] != 'c' || !isspace((unsigned char)p[1]))
		return (0);
	p += 2;
	while (isspace((unsigned char)*p))
		p++;
	if (strncmp(p, "None", 4) == 0 && (p[4] == '\0' || isspace((unsigned char)p[4])))
	{
		ent->color = 0;
		return (1);
	}
	if (*p != '#')
		return (0);
	ent->color = (uint32_t)strtoul(p + 1, &end, 16);
	return (end - (p + 1) == 6);
}

// takes: file buffer, length, cursor, cpp, number of colors
// returns: malloc'd palette, or NULL on error
static t_xpm_color	*read_palette(char *buf, long len, long *pos, int cpp,
		int ncolors)
{
	t_xpm_color	*tab;
	char		*lit;
	int			i;

	tab = malloc(sizeof(t_xpm_color) * ncolors);
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < ncolors)
	{
		lit = next_literal(buf, len, pos);
		if (!lit || !parse_color_line(lit, cpp, &tab[i]))
		{
			free(lit);
			free(tab);
			return (NULL);
		}
		free(lit);
	}
	return (tab);
}

// takes: palette, cpp, key pointer
// returns: color for the key, or NULL if not in the palette
static uint32_t	*find_color(t_xpm_color *tab, int ncolors, int cpp, char *key)
{
	int	i;

	i = -1;
	while (++i < ncolors)
	{
		if (memcmp(tab[i].key, key, cpp) == 0)
			return (&tab[i].color);
	}
	return (NULL);
}

// takes: file buffer, length, cursor, image, cpp, palette, ncolors
// mutates: fills img->pixels, returns 1 on success
static int	read_pixels(char *buf, long len, long *pos, t_image *img, int cpp,
		t_xpm_color *tab, int ncolors)
{
	char		*lit;
	uint32_t	*color;
	int			row;
	int			col;

	row = -1;
	while (++row < img->h)
	{
		lit = next_literal(buf, len, pos);
		if (!lit || (long)strlen(lit) < (long)img->w * cpp)
			return (free(lit), 0);
		col = -1;
		while (++col < img->w)
		{
			color = find_color(tab, ncolors, cpp, lit + col * cpp);
			if (!color)
				return (free(lit), 0);
			img->pixels[row * img->w + col] = *color;
		}
		free(lit);
	}
	return (1);
}

// takes: path
// returns: new image (0x00RRGGBB pixels), or NULL on any read or parse error
t_image	*gfx_load_xpm(const char *path)
{
	char		*buf;
	char		*head;
	long		len;
	long		pos;
	int			cols;
	int			rows;
	int			ncolors;
	int			cpp;
	t_xpm_color	*tab;
	t_image		*img;
	int			ok;

	buf = read_file(path, &len);
	if (!buf)
		return (NULL);
	pos = 0;
	head = next_literal(buf, len, &pos);
	if (!head || !parse_header(head, &cols, &rows, &ncolors, &cpp))
		return (free(head), free(buf), NULL);
	free(head);
	img = gfx_new_image(cols, rows);
	tab = read_palette(buf, len, &pos, cpp, ncolors);
	ok = img && tab && read_pixels(buf, len, &pos, img, cpp, tab, ncolors);
	free(tab);
	free(buf);
	if (!ok)
		return (gfx_free_image(img), NULL);
	return (img);
}

void	gfx_free_image(t_image *img)
{
	if (!img)
		return ;
	free(img->pixels);
	free(img);
}

// takes: destination image, top-left of glyph cell, color, character
// mutates: sets the pixels of set glyph bits (transparent background)
static void	draw_glyph(t_image *dst, int x, int y, uint32_t color,
		unsigned char c)
{
	int	row;
	int	col;
	int	px;
	int	py;

	if (c >= 128)
		return ;
	row = -1;
	while (++row < GLYPH_SIZE)
	{
		py = y + row;
		if (py < 0 || py >= dst->h)
			continue ;
		col = -1;
		while (++col < GLYPH_SIZE)
		{
			px = x + col;
			if (px < 0 || px >= dst->w)
				continue ;
			if (((unsigned char)font8x8_basic[c][row] >> col) & 1)
				dst->pixels[py * dst->w + px] = color & 0xFFFFFF;
		}
	}
}

// takes: destination image, top-left of the first glyph, color, string
// mutates: draws 8x8 glyphs into dst, clipped to its bounds
void	gfx_draw_text(t_image *dst, int x, int y, uint32_t color,
		const char *s)
{
	int	i;

	if (!dst || !s)
		return ;
	i = 0;
	while (s[i])
	{
		draw_glyph(dst, x + i * GLYPH_SIZE, y, color, (unsigned char)s[i]);
		i++;
	}
}
