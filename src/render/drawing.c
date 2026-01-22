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

// mutates: modifies pixel at (x, y) in image buffer

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

// draws a filled rectangle using point and size

// takes: game struct, position point, size, color

// mutates: draws rectangle on the image buffer

void	draw_rect(t_game *game, t_point pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(game, pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}

// clears the entire image buffer to black

// takes: game struct

// mutates: resets all pixels in image buffer to 0

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

// main render function called every frame by mlx_loop_hook

// takes: game struct

// returns: 0

int	render(t_game *game)
{
	process_movement(game);
	clear_image(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
