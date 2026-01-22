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
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TILE_SIZE 32

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
	char	**map;
	int		map_width;
	int		map_height;
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	int		floor_color;
	int		ceiling_color;
}	t_game;

int		create_window(void);
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);
void	draw_minimap(t_game *game);
int		render(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_circle_aa(t_game *game, int x0, int y0, int r, int color);
void	draw_line_aa(t_game *game, int x0, int y0, int x1, int y1, int color);

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

// utils
void	find_player(t_game *game);
int		parse_color(char *str);
char	*parse_texture_path(char *line);

#endif
