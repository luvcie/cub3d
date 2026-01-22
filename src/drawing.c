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

// puts a pixel in the image buffer (fast, no window update)
// takes: game struct, x, y, color
// mutates: image buffer data
void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

// draws a filled rectangle at position x,y with given size and color
// takes: game struct, x, y, size, color
// mutates: image buffer
static void	draw_rect(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// clears the entire image buffer to black
// takes: game struct
// mutates: image buffer
static void	clear_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < WIN_HEIGHT * game->line_len)
	{
		game->img_data[i] = 0;
		i++;
	}
}

// draws the map as a 2d grid with player position
// takes: game struct pointer
// mutates: image buffer
void	draw_minimap(t_game *game)
{
	int		x;
	int		y;
	int		color;

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
			draw_rect(game, x * TILE_SIZE, y * TILE_SIZE,
				TILE_SIZE - 1, color);
			x++;
		}
		y++;
	}
	x = (int)(game->player_x * TILE_SIZE);
	y = (int)(game->player_y * TILE_SIZE);
	draw_circle_aa(game, x, y, 7, 0xFF0000);
	draw_line_aa(game, x, y,
		x + (int)(cos(game->player_angle - 0.4) * 18),
		y + (int)(sin(game->player_angle - 0.4) * 18), 0xFF0000);
	draw_line_aa(game, x, y,
		x + (int)(cos(game->player_angle + 0.4) * 18),
		y + (int)(sin(game->player_angle + 0.4) * 18), 0xFF0000);
}

// main render function called every frame by mlx_loop_hook
// clears buffer, draws everything, pushes to window
// takes: game struct pointer
// returns: 0
int	render(t_game *game)
{
	clear_image(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
