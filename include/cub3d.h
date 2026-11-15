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

# include "libft.h"
# include "gfx.h"
# include <SDL3/SDL_keycode.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/time.h>
# include <math.h>
# include <stdbool.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define KEY_ESC SDLK_ESCAPE
# define KEY_W SDLK_W
# define KEY_A SDLK_A
# define KEY_S SDLK_S
# define KEY_D SDLK_D
# define KEY_R SDLK_R
# define KEY_M SDLK_M
# define KEY_H SDLK_H
# define KEY_TAB SDLK_TAB
# define KEY_LEFT SDLK_LEFT
# define KEY_RIGHT SDLK_RIGHT
# define KEY_1 SDLK_1
# define KEY_2 SDLK_2
# define KEY_3 SDLK_3
# define KEY_4 SDLK_4
# define KEY_5 SDLK_5
# define KEY_6 SDLK_6

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

typedef enum e_map_mode
{
	MAP_HIDDEN,
	MAP_MINI,
	MAP_FULL
}	t_map_mode;

typedef struct s_minimap_view
{
	t_point	pos;
	int		size;
	double	scale;
	double	world_x;
	double	world_y;
}	t_minimap_view;

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
	t_gfx	*gfx;
	t_image	*frame;
	int		win_width;
	int		win_height;
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
	char	*current_line;
	int		floor_color;
	int		ceiling_color;
	bool	floor_set;
	bool	ceiling_set;
	bool	screensaver;
	bool	screensaver_target;
	int		screensaver_direction;
	double	screensaver_x;
	double	screensaver_y;
	bool	show_rays;
	t_map_mode	map_mode;
	t_minimap_view	minimap;
	bool	show_help;
	t_point	*ray_hits;
	t_image	*tex[4];
}	t_game;

void	init_view(t_game *game);
void	key_press(int keycode, void *param);
void	key_release(int keycode, void *param);
void	mouse_move(int x, int y, void *param);
void	close_window(void *param);
void	change_resolution(t_game *game, int width, int height);
void	handle_resolution_keys(int keycode, t_game *game);
void	process_movement(t_game *game);
void	screensaver_step(t_game *game);
void	draw_minimap(t_game *game);
void	update_minimap_view(t_game *game);
t_point	world_to_minimap(t_game *game, double wx, double wy);
void	draw_help_menu(t_game *game);
void	render(void *param);
void	draw_overlay(void *param);
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_circle_aa(t_game *game, t_point center, int r, int color);
void	draw_line_aa(t_game *game, t_line line);
int		blend_color(int fg, int bg, int intensity);
int		get_pixel_color(t_game *game, int x, int y);

// raycasting
void	render_3d(t_game *game);
void	draw_rays_minimap(t_game *game);
t_point	minimap_ray_hit(t_game *game, const t_ray *ray);
void	load_textures(t_game *game);
int		get_tex_pixel(t_image *tex, int x, int y);
void	init_ray(t_game *game, t_ray *ray, int x);
void	cast_ray(t_game *game, t_ray *ray);
void	calc_wall(t_game *game, t_ray *ray);

// parsing
char	*get_next_line(int fd);
void	parse_map(char *filename, t_game *game);
void	validate_extension(t_game *game, char *filename);
void	validate_config(t_game *game);
void	validate_textures(t_game *game);
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
