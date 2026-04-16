/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:20:11 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 02:56:59 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "mlx_events.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/time.h>
# include <math.h>
# include <stdbool.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_R 114
# define KEY_M 109
# define KEY_H 104
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_1 49
# define KEY_2 50
# define KEY_3 51
# define KEY_4 52
# define KEY_5 53
# define KEY_6 54

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TILE_SIZE 32
# define MOVE_SPEED 0.06
# define PLAYER_RADIUS 0.2
# define ROT_SPEED 0.08
# define FOV 0.66
# define MAX_DEPTH 64

# define MINIMAP_SIZE 180
# define MINIMAP_TILE 12
# define MINIMAP_MARGIN 10

# define HELP_MENU_WIDTH 140
# define HELP_MENU_HEIGHT 350
# define HELP_MENU_MARGIN_R 0
# define HELP_MENU_MARGIN_B 80

# define WALL_NORTH 0
# define WALL_SOUTH 1
# define WALL_EAST 2
# define WALL_WEST 3

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}	t_keys;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_line
{
	t_point	p0;
	t_point	p1;
	int		color;
}	t_line;

typedef struct s_tex
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		sign_x;
	int		sign_y;
	int		side;
	int		wall_dir;
	double	perp_dist;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	draw_start_f;
	double	draw_end_f;
}	t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		win_width;
	int		win_height;
	int		bpp;
	int		line_len;
	int		endian;
	double	player_x;
	double	player_y;
	double	player_angle;
	long	last_time;
	double	delta_time;
	t_keys	keys;
	int		mouse_x;
	char	**map;
	int		map_width;
	int		map_height;
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	int		floor_color;
	int		ceiling_color;
	bool	floor_set;
	bool	ceiling_set;
	bool	show_rays;
	bool	show_minimap;
	bool	show_help;
	t_tex	tex[4];
}	t_game;

void	create_window(t_game *game);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		mouse_move(int x, int y, void *param);
int		close_window(void *param);
void	change_resolution(t_game *game, int width, int height);
void	handle_resolution_keys(int keycode, t_game *game);
void	process_movement(t_game *game);
void	draw_minimap(t_game *game);
t_point	world_to_minimap(t_game *game, double wx, double wy);
void	draw_help_menu(t_game *game);
int		render(void *param);
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_rect(t_game *game, t_point pos, int size, int color);
void	draw_circle_aa(t_game *game, t_point center, int r, int color);
void	draw_line_aa(t_game *game, t_line line);
int		blend_color(int fg, int bg, int intensity);
int		get_pixel_color(t_game *game, int x, int y);

// raycasting
void	render_3d(t_game *game);
void	draw_rays_minimap(t_game *game);
void	load_textures(t_game *game);
int		get_tex_pixel(t_tex *tex, int x, int y);
void	init_ray(t_game *game, t_ray *ray, int x);
void	cast_ray(t_game *game, t_ray *ray);
void	calc_wall(t_game *game, t_ray *ray);
void	cast_ray_minimap(t_game *game, t_ray *ray);

// parsing
char	*get_next_line(int fd);
void	parse_map(char *filename, t_game *game);
void	validate_extension(t_game *game, char *filename);
void	validate_config(t_game *game);
void	validate_walls(t_game *game);
void	validate_elements(t_game *game);
void	print_map_error(t_game *game, char *message);
void	free_game_map(t_game *game);
void	free_textures(t_game *game);
void	free_game(t_game *game);

// parse_config
bool	is_config_line(char *line, t_game *game);
bool	is_empty_line(char *line);
void	process_map_line(t_game *game, char *line, int *map_index);

// utils
void	find_player(t_game *game);
int		parse_color(t_game *game, char *str);
char	*parse_texture_path(t_game *game, char *line);

#endif
