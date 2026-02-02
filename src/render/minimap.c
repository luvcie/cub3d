/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:52:17 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 02:57:38 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// converts world coords to minimap screen coords, player is always centered
// takes: game struct, world x and y
// returns: screen point for minimap
t_point	world_to_minimap(t_game *game, double wx, double wy)
{
	t_point	result;
	int		center;

	center = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	result.x = center + (int)((wx - game->player_x) * MINIMAP_TILE);
	result.y = center + (int)((wy - game->player_y) * MINIMAP_TILE);
	return (result);
}

// draws a rect clipped to minimap bounds
// takes: game struct, position, size, color
// mutates: draws pixels within minimap area
static void	draw_minimap_rect(t_game *game, t_point pos, int size, int color)
{
	int	x;
	int	y;
	int	max_bound;

	max_bound = MINIMAP_MARGIN + MINIMAP_SIZE;
	y = pos.y;
	while (y < pos.y + size)
	{
		x = pos.x;
		while (x < pos.x + size)
		{
			if (x >= MINIMAP_MARGIN && x < max_bound
				&& y >= MINIMAP_MARGIN && y < max_bound)
				put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

// draws the map tiles visible in the minimap viewport
// takes: game struct
// mutates: draws map tiles on the image buffer
static void	draw_map_tiles(t_game *game)
{
	int		x;
	int		y;
	int		color;
	t_point	pos;

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
			pos = world_to_minimap(game, (double)x, (double)y);
			draw_minimap_rect(game, pos, MINIMAP_TILE - 1, color);
			x++;
		}
		y++;
	}
}

// draws the player at the center of the minimap with direction cone
// takes: game struct
// mutates: draws player and direction cone on the image buffer
static void	draw_player(t_game *game)
{
	t_point	center;
	t_line	line;
	double	angle;

	center.x = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	center.y = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	draw_circle_aa(game, center, 5, 0xFF0000);
	angle = game->player_angle;
	line.p0 = center;
	line.p1.x = center.x + (int)(cos(angle - 0.4) * 14);
	line.p1.y = center.y + (int)(sin(angle - 0.4) * 14);
	line.color = 0xFF0000;
	draw_line_aa(game, line);
	line.p1.x = center.x + (int)(cos(angle + 0.4) * 14);
	line.p1.y = center.y + (int)(sin(angle + 0.4) * 14);
	draw_line_aa(game, line);
}

// draws a border around the minimap
// takes: game struct
// mutates: draws border pixels on the image buffer
static void	draw_minimap_border(t_game *game)
{
	int	i;
	int	max_bound;

	max_bound = MINIMAP_MARGIN + MINIMAP_SIZE;
	i = MINIMAP_MARGIN;
	while (i <= max_bound)
	{
		put_pixel(game, i, MINIMAP_MARGIN, 0x888888);
		put_pixel(game, i, max_bound, 0x888888);
		put_pixel(game, MINIMAP_MARGIN, i, 0x888888);
		put_pixel(game, max_bound, i, 0x888888);
		i++;
	}
}

// draws the complete minimap with fixed viewport
// takes: game struct
// mutates: draws entire minimap scene
void	draw_minimap(t_game *game)
{
	draw_map_tiles(game);
	if (game->show_rays)
		draw_rays_minimap(game);
	draw_player(game);
	draw_minimap_border(game);
}
