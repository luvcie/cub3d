/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:32:18 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/22 14:20:26 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// draws a filled rectangle at position x,y with given size and color
// takes: mlx, win, x, y, size, color
// mutates: window pixels
static void	draw_tile(void *mlx, void *win, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(mlx, win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// draws the map as a 2d grid with player position
// takes: game struct pointer
// mutates: window pixels
void	draw_minimap(t_game *game)
{
	int		x;
	int		y;
	int		tile_size;
	int		color;

	tile_size = 32;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x333333;
			draw_tile(game->mlx, game->win, x * tile_size, y * tile_size,
				tile_size - 1, color);
			x++;
		}
		y++;
	}
	x = (int)(game->player_x * tile_size);
	y = (int)(game->player_y * tile_size);
	draw_tile(game->mlx, game->win, x - 4, y - 4, 8, 0xFF0000);
}
