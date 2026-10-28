#ifndef GFX_H
# define GFX_H

# include <stdbool.h>
# include <stdint.h>

// window, input and drawing on top of SDL3, one window per program

typedef struct s_image
{
	int			w;
	int			h;
	uint32_t	*pixels;
}	t_image;

typedef struct s_gfx	t_gfx;

// key codes are SDL keycodes (SDLK_* from <SDL3/SDL_keycode.h>)
typedef struct s_gfx_hooks
{
	void	(*frame)(void *param);
	// runs after the frame is drawn on screen, the only place gfx_draw_text works
	void	(*overlay)(void *param);
	void	(*key_press)(int key, void *param);
	void	(*key_release)(int key, void *param);
	void	(*mouse_move)(int x, int y, void *param);
	void	(*close)(void *param);
	void	*param;
}	t_gfx_hooks;

t_gfx	*gfx_init(const char *title, int w, int h);
void	gfx_quit(t_gfx *gfx);
bool	gfx_resize(t_gfx *gfx, int w, int h);
void	gfx_screen_size(t_gfx *gfx, int *w, int *h);
t_image	*gfx_frame(t_gfx *gfx);
void	gfx_run(t_gfx *gfx, const t_gfx_hooks *hooks);

t_image	*gfx_new_image(int w, int h);
t_image	*gfx_load_xpm(const char *path);
void	gfx_free_image(t_image *img);
void	gfx_draw_text(t_gfx *gfx, int x, int y, uint32_t color,
			const char *s);

#endif
