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

typedef struct s_game
{
	void	*mlx;
	void	*win;
	double	player_x;
	double	player_y;
	double	player_angle;
}	t_game;

int		create_window(void);
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);
void	draw_triangle_direct(void *mlx, void *win);
void	draw_triangle_buffer(void *mlx, void *win);
void	draw_pentagram_direct(void *mlx, void *win);

#endif
