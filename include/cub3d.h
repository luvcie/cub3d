/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:20:11 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/03 06:34:46 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/time.h>
# include <math.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_R 114
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TILE_SIZE 32
# define MOVE_SPEED 0.02
# define PLAYER_RADIUS 0.2
# define ROT_SPEED 0.04
# define FOV 0.66
# define MAX_DEPTH 64

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
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

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		sign_x;
	int		sign_y;
	int		side;
	double	perp_dist;
}	t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		bpp;
	int		line_len;
	int		endian;
	double	player_x;
	double	player_y;
	double	player_angle;
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
	int		show_rays;
}	t_game;

int		create_window(void);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		mouse_move(int x, int y, t_game *game);
int		close_window(t_game *game);
void	process_movement(t_game *game);
void	draw_minimap(t_game *game);
int		render(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_rect(t_game *game, t_point pos, int size, int color);
void	draw_circle_aa(t_game *game, t_point center, int r, int color);
void	draw_line_aa(t_game *game, t_line line);
int		blend_color(int fg, int bg, int intensity);
int		get_pixel_color(t_game *game, int x, int y);

// raycasting
void	draw_rays_minimap(t_game *game);

// parsing
char	*get_next_line(int fd);
void	parse_map(char *filename, t_game *game);
void	validate_extension(char *filename);
void	validate_config(t_game *game);
void	validate_walls(t_game *game);
void	validate_elements(t_game *game);
void	print_map_error(char *message);
void	free_game_map(t_game *game);
void	free_game(t_game *game);

// parse_config
int		is_config_line(char *line, t_game *game);
int		is_empty_line(char *line);
void	process_map_line(t_game *game, char *line, int *map_index);

// utils
void	find_player(t_game *game);
int		parse_color(char *str);
char	*parse_texture_path(char *line);

#endif
