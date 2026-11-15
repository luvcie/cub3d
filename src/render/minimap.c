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

static void	draw_player(t_game *game)
{
	t_line	line;
	t_ray	ray;
	double	length;
	int		edge;

	line.p0 = world_to_minimap(game, game->player_x, game->player_y);
	draw_circle_aa(game, line.p0, 5, 0xFF0000);
	line.color = 0xFF0000;
	edge = 0;
	while (edge < 2)
	{
		init_ray(game, &ray, edge * (game->win_width - 1));
		length = hypot(ray.dir_x, ray.dir_y);
		line.p1.x = line.p0.x + (int)(14 * ray.dir_x / length);
		line.p1.y = line.p0.y + (int)(14 * ray.dir_y / length);
		draw_line_aa(game, line);
		edge++;
	}
}

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

void	draw_minimap(t_game *game)
{
	draw_map_tiles(game);
	if (game->show_rays)
		draw_rays_minimap(game);
	draw_player(game);
	draw_minimap_border(game);
}
