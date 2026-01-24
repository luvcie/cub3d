/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:52:17 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/25 02:53:30 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// draws the map tiles as a 2d grid
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
			pos = (t_point){x * TILE_SIZE, y * TILE_SIZE};
			draw_rect(game, pos, TILE_SIZE - 1, color);
			x++;
		}
		y++;
	}
}

// draws the player circle and direction cone
// takes: game struct
// mutates: draws player and direction cone on the image buffer
static void	draw_player(t_game *game)
{
	t_point	center;
	t_line	line;
	double	angle;

	center.x = (int)(game->player_x * TILE_SIZE);
	center.y = (int)(game->player_y * TILE_SIZE);
	draw_circle_aa(game, center, 7, 0xFF0000);
	angle = game->player_angle;
	line.p0 = center;
	line.p1.x = center.x + (int)(cos(angle - 0.4) * 18);
	line.p1.y = center.y + (int)(sin(angle - 0.4) * 18);
	line.color = 0xFF0000;
	draw_line_aa(game, line);
	line.p1.x = center.x + (int)(cos(angle + 0.4) * 18);
	line.p1.y = center.y + (int)(sin(angle + 0.4) * 18);
	draw_line_aa(game, line);
}

// draws the complete minimap
// takes: game struct
// mutates: draws entire minimap scene
void	draw_minimap(t_game *game)
{
	draw_map_tiles(game);
	if (game->show_rays)
		draw_rays_minimap(game);
	draw_player(game);
}
