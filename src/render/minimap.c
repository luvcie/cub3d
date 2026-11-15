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

static void	draw_minimap_rect(t_game *game, t_point_f pos, t_point_f end,
		int color, int opacity)
{
	int	x;
	int	y;

	pos.x = fmax(pos.x, game->minimap.pos.x);
	pos.y = fmax(pos.y, game->minimap.pos.y);
	end.x = fmin(end.x, game->minimap.pos.x + game->minimap.size);
	end.y = fmin(end.y, game->minimap.pos.y + game->minimap.size);
	end.x = floor(end.x);
	end.y = floor(end.y);
	y = pos.y;
	while (y < end.y)
	{
		x = pos.x;
		while (x < end.x)
		{
			if (opacity == 255)
				put_pixel(game, x, y, color);
			else
				put_pixel(game, x, y, blend_color(color,
						get_pixel_color(game, x, y), opacity));
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
	int		opacity;
	t_point_f	pos;
	t_point_f	end;

	opacity = 255;
	if (game->map_mode == MAP_FULL)
		opacity = 160;
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
			end = world_to_minimap(game, x + 1.0, y + 1.0);
			if (game->minimap.scale >= 4)
				end = (t_point_f){end.x - 1, end.y - 1};
			draw_minimap_rect(game, pos, end, color, opacity);
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
		line.p1.x = line.p0.x + 14 * ray.dir_x / length;
		line.p1.y = line.p0.y + 14 * ray.dir_y / length;
		draw_line_aa(game, line);
		edge++;
	}
}

static void	draw_minimap_border(t_game *game)
{
	int		i;
	t_point	pos;
	int		size;

	pos = game->minimap.pos;
	size = game->minimap.size;
	i = 0;
	while (i <= size)
	{
		put_pixel(game, pos.x + i, pos.y, 0x888888);
		put_pixel(game, pos.x + i, pos.y + size, 0x888888);
		put_pixel(game, pos.x, pos.y + i, 0x888888);
		put_pixel(game, pos.x + size, pos.y + i, 0x888888);
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	t_point_f	pos;
	t_point_f	end;

	if (game->map_mode == MAP_FULL)
	{
		pos = (t_point_f){game->minimap.pos.x, game->minimap.pos.y};
		end.x = game->minimap.pos.x + game->minimap.size;
		end.y = game->minimap.pos.y + game->minimap.size;
		draw_minimap_rect(game, pos, end, 0x111111, 96);
	}
	draw_map_tiles(game);
	if (game->show_rays)
		draw_rays_minimap(game);
	draw_player(game);
	draw_minimap_border(game);
}
