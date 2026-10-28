#ifndef MLX_H
# define MLX_H

// MiniLibX-style API on SDL2, with typed hook functions

void	*mlx_init(void);
int		mlx_get_screen_size(void *mlx, int *w, int *h);
void	*mlx_new_window(void *mlx, int w, int h, char *title);
void	*mlx_new_image(void *mlx, int w, int h);
char	*mlx_get_data_addr(void *img, int *bpp, int *line_len, int *endian);
int		mlx_put_image_to_window(void *mlx, void *win, void *img, int x, int y);
int		mlx_string_put(void *mlx, void *win, int x, int y, int color, char *str);
void	*mlx_xpm_file_to_image(void *mlx, char *file, int *w, int *h);
int		mlx_loop_hook(void *mlx, int (*f)(void *), void *param);
int		mlx_key_press_hook(void *win, int (*f)(int, void *), void *param);
int		mlx_key_release_hook(void *win, int (*f)(int, void *), void *param);
int		mlx_motion_hook(void *win, int (*f)(int, int, void *), void *param);
int		mlx_close_hook(void *win, int (*f)(void *), void *param);
int		mlx_loop(void *mlx);
int		mlx_destroy_image(void *mlx, void *img);
int		mlx_destroy_window(void *mlx, void *win);
int		mlx_destroy_display(void *mlx);

#endif
