// Window, input, drawing and BMP loading on top of SDL3.
// The frame is a 0x00RRGGBB buffer, shown once per loop iteration.

#include "gfx.h"
#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __EMSCRIPTEN__
# include <emscripten.h>
#endif

struct s_gfx
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	t_image			*frame;
	t_gfx_hooks		hooks;
};

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
// mutates: uploads the current frame, draws it, then the overlay, and shows it
// a frame hook may resize: read the frame and texture here, not cached
static void	present(t_gfx *gfx)
{
	SDL_UpdateTexture(gfx->texture, NULL, gfx->frame->pixels,
		gfx->frame->w * (int)sizeof(uint32_t));
	SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 0, 255);
	SDL_RenderClear(gfx->renderer);
	SDL_RenderTexture(gfx->renderer, gfx->texture, NULL, NULL);
	if (gfx->hooks.overlay)
		gfx->hooks.overlay(gfx->hooks.param);
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

// takes: converted surface, image of the same size
// mutates: copies the rows into img->pixels, skipping the row padding
static void	copy_rows(SDL_Surface *conv, t_image *img)
{
	const uint8_t	*src;
	int				y;

	y = -1;
	while (++y < img->h)
	{
		src = (const uint8_t *)conv->pixels + (size_t)y * conv->pitch;
		memcpy(img->pixels + (size_t)y * img->w, src,
			(size_t)img->w * sizeof(uint32_t));
	}
}

// takes: path to a BMP file
// returns: new image (0x00RRGGBB pixels), or NULL on any read error
t_image	*gfx_load_bmp(const char *path)
{
	SDL_Surface	*surf;
	SDL_Surface	*conv;
	t_image		*img;

	surf = SDL_LoadBMP(path);
	if (!surf)
		return (NULL);
	conv = SDL_ConvertSurface(surf, SDL_PIXELFORMAT_XRGB8888);
	SDL_DestroySurface(surf);
	if (!conv)
		return (NULL);
	img = gfx_new_image(conv->w, conv->h);
	if (img)
		copy_rows(conv, img);
	SDL_DestroySurface(conv);
	return (img);
}

void	gfx_free_image(t_image *img)
{
	if (!img)
		return ;
	free(img->pixels);
	free(img);
}

// takes: gfx, top-left of the text (8x8 glyphs), color 0x00RRGGBB, string
// mutates: draws the text with the renderer, only valid in the overlay hook
void	gfx_draw_text(t_gfx *gfx, int x, int y, uint32_t color,
		const char *s)
{
	if (!gfx || !s)
		return ;
	SDL_SetRenderDrawColor(gfx->renderer, (color >> 16) & 0xFF,
		(color >> 8) & 0xFF, color & 0xFF, 255);
	SDL_RenderDebugText(gfx->renderer, (float)x, (float)y, s);
}
