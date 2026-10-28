// MiniLibX-compatible shim on top of SDL2.
// Each window owns a 0x00RRGGBB framebuffer. Drawing calls write into it,
// and the framebuffer is uploaded and presented once per loop iteration.

#include "mlx.h"
#include <SDL.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "font8x8_basic.h"
#ifdef __EMSCRIPTEN__
# include <emscripten.h>
#endif

#define X11_KEYPRESS 2
#define X11_KEYRELEASE 3
#define X11_MOTIONNOTIFY 6
#define X11_DESTROYNOTIFY 17

#define X11_KEY_ESCAPE 65307
#define X11_KEY_LEFT 65361
#define X11_KEY_UP 65362
#define X11_KEY_RIGHT 65363
#define X11_KEY_DOWN 65364

#define GLYPH_SIZE 8
#define GLYPH_ADVANCE 8
#define XPM_MAX_CPP 2
#define XPM_COLOR_NONE 0

typedef struct s_hook
{
	int		(*fn)();
	void	*param;
}	t_hook;

typedef struct s_img
{
	int			w;
	int			h;
	uint32_t	*pixels;
}	t_img;

typedef struct s_win
{
	SDL_Window		*sdl_win;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	int				w;
	int				h;
	uint32_t		*fb;
	t_hook			on_key_press;
	t_hook			on_key_release;
	t_hook			on_motion;
	t_hook			on_destroy;
}	t_win;

typedef struct s_mlx
{
	t_win	*win;
	t_hook	on_loop;
}	t_mlx;

typedef struct s_xpm_color
{
	char		key[XPM_MAX_CPP];
	uint32_t	color;
}	t_xpm_color;

// takes: hook slot, callback, parameter
// mutates: stores both in the slot
static void	set_hook(t_hook *hook, int (*fn)(), void *param)
{
	hook->fn = fn;
	hook->param = param;
}

// takes: window
// mutates: destroys SDL objects and frees the window (safe on partial init)
static void	free_win(t_win *win)
{
	if (win->texture)
		SDL_DestroyTexture(win->texture);
	if (win->renderer)
		SDL_DestroyRenderer(win->renderer);
	if (win->sdl_win)
		SDL_DestroyWindow(win->sdl_win);
	free(win->fb);
	free(win);
}

// takes: SDL keycode
// returns: X11 keysym the game expects (printable ASCII already matches)
static int	map_keycode(SDL_Keycode key)
{
	if (key == SDLK_ESCAPE)
		return (X11_KEY_ESCAPE);
	if (key == SDLK_LEFT)
		return (X11_KEY_LEFT);
	if (key == SDLK_UP)
		return (X11_KEY_UP);
	if (key == SDLK_RIGHT)
		return (X11_KEY_RIGHT);
	if (key == SDLK_DOWN)
		return (X11_KEY_DOWN);
	return ((int)key);
}

// takes: mlx, keycode, released flag
// mutates: may run the key hook, which can destroy or recreate the window
static void	call_key(t_mlx *mlx, int keycode, int released)
{
	t_win	*win;
	int		(*fn)();
	void	*param;

	win = mlx->win;
	if (!win)
		return ;
	if (released)
	{
		fn = win->on_key_release.fn;
		param = win->on_key_release.param;
	}
	else
	{
		fn = win->on_key_press.fn;
		param = win->on_key_press.param;
	}
	if (fn)
		((int (*)(int, void *))fn)(keycode, param);
}

// takes: mlx, pointer position
// mutates: may run the motion hook
static void	call_motion(t_mlx *mlx, int x, int y)
{
	t_win	*win;
	int		(*fn)();
	void	*param;

	win = mlx->win;
	if (!win || !win->on_motion.fn)
		return ;
	fn = win->on_motion.fn;
	param = win->on_motion.param;
	((int (*)(int, int, void *))fn)(x, y, param);
}

// takes: mlx
// mutates: may run the destroy hook (window close)
static void	call_destroy(t_mlx *mlx)
{
	t_win	*win;
	int		(*fn)();
	void	*param;

	win = mlx->win;
	if (!win || !win->on_destroy.fn)
		return ;
	fn = win->on_destroy.fn;
	param = win->on_destroy.param;
	((int (*)(void *))fn)(param);
}

// takes: mlx
// mutates: drains the SDL event queue and dispatches to the hooks
static void	poll_events(t_mlx *mlx)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
#ifdef __EMSCRIPTEN__
		// browsers use ESC to leave fullscreen/pointer lock, not the game
		if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			&& e.key.keysym.sym == SDLK_ESCAPE)
			continue ;
#endif
		if (e.type == SDL_KEYDOWN && !e.key.repeat)
			call_key(mlx, map_keycode(e.key.keysym.sym), 0);
		else if (e.type == SDL_KEYUP)
			call_key(mlx, map_keycode(e.key.keysym.sym), 1);
		else if (e.type == SDL_MOUSEMOTION)
			call_motion(mlx, e.motion.x, e.motion.y);
		else if (e.type == SDL_QUIT
			|| (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE))
			call_destroy(mlx);
	}
}

// takes: mlx
// mutates: uploads the window framebuffer and shows it (no-op without window)
static void	present(t_mlx *mlx)
{
	t_win	*win;

	win = mlx->win;
	if (!win)
		return ;
	SDL_UpdateTexture(win->texture, NULL, win->fb,
		win->w * (int)sizeof(uint32_t));
	SDL_RenderClear(win->renderer);
	SDL_RenderCopy(win->renderer, win->texture, NULL, NULL);
	SDL_RenderPresent(win->renderer);
}

// one loop iteration: events, loop hook, present
// takes: mlx as void pointer (for emscripten_set_main_loop_arg)
static void	step(void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = mlx_ptr;
	poll_events(mlx);
	if (mlx->on_loop.fn)
		((int (*)(void *))mlx->on_loop.fn)(mlx->on_loop.param);
	present(mlx);
}

void	*mlx_init(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
		free(mlx);
		return (NULL);
	}
	mlx->win = NULL;
	mlx->on_loop.fn = NULL;
	mlx->on_loop.param = NULL;
	return (mlx);
}

int	mlx_get_screen_size(void *mlx, int *w, int *h)
{
	(void)mlx;
#ifdef __EMSCRIPTEN__
	*w = 1280;
	*h = 720;
	return (0);
#else
	SDL_DisplayMode	mode;

	if (SDL_GetDesktopDisplayMode(0, &mode) != 0)
		return (-1);
	*w = mode.w;
	*h = mode.h;
	return (0);
#endif
}

// takes: mlx, size, title
// returns: new window, or NULL on failure
// mutates: if a window already exists it is destroyed first (one at a time)
void	*mlx_new_window(void *mlx_ptr, int w, int h, char *title)
{
	t_mlx	*mlx;
	t_win	*win;

	mlx = mlx_ptr;
	if (!mlx || w <= 0 || h <= 0)
		return (NULL);
	if (mlx->win)
		mlx_destroy_window(mlx, mlx->win);
	win = calloc(1, sizeof(t_win));
	if (!win)
		return (NULL);
	win->w = w;
	win->h = h;
	win->fb = calloc((size_t)w * h, sizeof(uint32_t));
	win->sdl_win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, w, h, 0);
	if (!win->fb || !win->sdl_win)
		return (free_win(win), NULL);
	win->renderer = SDL_CreateRenderer(win->sdl_win, -1,
			SDL_RENDERER_PRESENTVSYNC);
	if (!win->renderer)
		return (free_win(win), NULL);
	win->texture = SDL_CreateTexture(win->renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, w, h);
	if (!win->texture)
		return (free_win(win), NULL);
	SDL_SetTextureBlendMode(win->texture, SDL_BLENDMODE_NONE);
	mlx->win = win;
	return (win);
}

void	*mlx_new_image(void *mlx, int w, int h)
{
	t_img	*img;

	(void)mlx;
	if (w <= 0 || h <= 0)
		return (NULL);
	img = malloc(sizeof(t_img));
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

// takes: image, output bpp/line_len/endian
// returns: pointer to 0x00RRGGBB pixels
char	*mlx_get_data_addr(void *img_ptr, int *bpp, int *line_len, int *endian)
{
	t_img	*img;

	img = img_ptr;
	if (!img)
		return (NULL);
	*bpp = 32;
	*line_len = img->w * (int)sizeof(uint32_t);
	*endian = 0;
	return ((char *)img->pixels);
}

// takes: destination window, source image, top-left position
// mutates: copies the visible part of img into win->fb
static void	blit(t_win *win, t_img *img, int x, int y)
{
	int	sx;
	int	sy;
	int	cw;
	int	ch;
	int	r;

	sx = 0;
	sy = 0;
	if (x < 0)
	{
		sx = -x;
		x = 0;
	}
	if (y < 0)
	{
		sy = -y;
		y = 0;
	}
	cw = img->w - sx;
	ch = img->h - sy;
	if (x + cw > win->w)
		cw = win->w - x;
	if (y + ch > win->h)
		ch = win->h - y;
	if (cw <= 0 || ch <= 0)
		return ;
	r = -1;
	while (++r < ch)
		memcpy(&win->fb[(y + r) * win->w + x],
			&img->pixels[(sy + r) * img->w + sx], cw * sizeof(uint32_t));
}

// does not present, the loop does that
int	mlx_put_image_to_window(void *mlx, void *win_ptr, void *img_ptr,
		int x, int y)
{
	(void)mlx;
	if (!win_ptr || !img_ptr)
		return (-1);
	blit(win_ptr, img_ptr, x, y);
	return (0);
}

// takes: window, top-left of glyph cell, color, character
// mutates: sets the framebuffer pixels of set glyph bits (transparent bg)
static void	draw_glyph(t_win *win, int x, int y, uint32_t color,
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
		if (py < 0 || py >= win->h)
			continue ;
		col = -1;
		while (++col < GLYPH_SIZE)
		{
			px = x + col;
			if (px < 0 || px >= win->w)
				continue ;
			if (((unsigned char)font8x8_basic[c][row] >> col) & 1)
				win->fb[py * win->w + px] = color & 0xFFFFFF;
		}
	}
}

// y is the baseline (minilibx convention), so glyph tops are at y - 8
int	mlx_string_put(void *mlx, void *win_ptr, int x, int y, int color,
		char *str)
{
	int	i;

	(void)mlx;
	if (!win_ptr || !str)
		return (-1);
	i = 0;
	while (str[i])
	{
		draw_glyph(win_ptr, x + i * GLYPH_ADVANCE, y - GLYPH_SIZE,
			(uint32_t)color, (unsigned char)str[i]);
		i++;
	}
	return (0);
}

// takes: image, output bpp/line_len/endian
// mutates: frees img pixels and img
int	mlx_destroy_image(void *mlx, void *img_ptr)
{
	t_img	*img;

	(void)mlx;
	img = img_ptr;
	if (!img)
		return (-1);
	free(img->pixels);
	free(img);
	return (0);
}

// takes: mlx, window
// mutates: destroys the window only if it is the current one
int	mlx_destroy_window(void *mlx_ptr, void *win_ptr)
{
	t_mlx	*mlx;
	t_win	*win;

	mlx = mlx_ptr;
	win = win_ptr;
	if (!mlx || !win || mlx->win != win)
		return (-1);
	mlx->win = NULL;
	free_win(win);
	return (0);
}

// does not free the mlx struct, the game does that
int	mlx_destroy_display(void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = mlx_ptr;
	if (!mlx)
		return (-1);
	if (mlx->win)
		mlx_destroy_window(mlx, mlx->win);
	SDL_Quit();
	return (0);
}

// takes: window, x event type, x mask (ignored), callback, parameter
// mutates: stores the hook for keypress, keyrelease, motion or destroy
int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(),
		void *param)
{
	t_win	*win;

	(void)x_mask;
	win = win_ptr;
	if (!win)
		return (-1);
	if (x_event == X11_KEYPRESS)
		set_hook(&win->on_key_press, funct, param);
	else if (x_event == X11_KEYRELEASE)
		set_hook(&win->on_key_release, funct, param);
	else if (x_event == X11_MOTIONNOTIFY)
		set_hook(&win->on_motion, funct, param);
	else if (x_event == X11_DESTROYNOTIFY)
		set_hook(&win->on_destroy, funct, param);
	return (0);
}

int	mlx_loop_hook(void *mlx_ptr, int (*funct)(), void *param)
{
	t_mlx	*mlx;

	mlx = mlx_ptr;
	if (!mlx)
		return (-1);
	set_hook(&mlx->on_loop, funct, param);
	return (0);
}

int	mlx_loop(void *mlx)
{
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(step, mlx, 0, 1);
#else
	while (1)
		step(mlx);
#endif
	return (0);
}

// takes: path
// returns: malloc'd file contents (NUL terminated), size in *len, or NULL
static char	*read_file(char *path, long *len)
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
		ent->color = XPM_COLOR_NONE;
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
static int	read_pixels(char *buf, long len, long *pos, t_img *img, int cpp,
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

// takes: mlx, path, output width/height
// returns: new image, or NULL on any read or parse error
void	*mlx_xpm_file_to_image(void *mlx, char *file, int *w, int *h)
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
	t_img		*img;
	int			ok;

	buf = read_file(file, &len);
	if (!buf)
		return (NULL);
	pos = 0;
	head = next_literal(buf, len, &pos);
	if (!head || !parse_header(head, &cols, &rows, &ncolors, &cpp))
		return (free(head), free(buf), NULL);
	free(head);
	img = mlx_new_image(mlx, cols, rows);
	tab = read_palette(buf, len, &pos, cpp, ncolors);
	ok = img && tab && read_pixels(buf, len, &pos, img, cpp, tab, ncolors);
	free(tab);
	free(buf);
	if (!ok)
		return (mlx_destroy_image(mlx, img), NULL);
	if (w)
		*w = cols;
	if (h)
		*h = rows;
	return (img);
}
