/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:41:33 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 02:57:53 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static double	axis_limit(double origin, double dir, double center, double half)
{
	if (dir > 0)
		return ((center + half - origin) / dir);
	if (dir < 0)
		return ((center - half - origin) / dir);
	return (INFINITY);
}

t_point_f	minimap_ray_hit(t_game *game, const t_ray *ray)
{
	double	hit_x;
	double	hit_y;
	double	half;
	double	dist;

	// Keep the antialiased edge inside the square minimap border.
	half = (game->minimap.size / 2 - 1) / game->minimap.scale;
	dist = fmin(ray->perp_dist, axis_limit(game->player_x,
			ray->dir_x, game->minimap.world_x, half));
	dist = fmin(dist, axis_limit(game->player_y,
			ray->dir_y, game->minimap.world_y, half));
	hit_x = game->player_x + ray->dir_x * dist;
	hit_y = game->player_y + ray->dir_y * dist;
	return (world_to_minimap(game, hit_x, hit_y));
}

void	draw_rays_minimap(t_game *game)
{
	t_line	line;
	int		i;

	line.p0 = world_to_minimap(game, game->player_x, game->player_y);
	line.color = 0xF0EAD6;
	i = 0;
	while (i < game->win_width)
	{
		line.p1 = game->ray_hits[i];
		draw_line_aa(game, line);
		i++;
	}
}
