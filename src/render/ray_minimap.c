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

// converts world coords to minimap screen coords, player is always centered
t_point	world_to_minimap(t_game *game, double wx, double wy)
{
	t_point	result;
	int		center;

	center = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	result.x = center + (int)((wx - game->player_x) * MINIMAP_TILE);
	result.y = center + (int)((wy - game->player_y) * MINIMAP_TILE);
	return (result);
}

t_point	minimap_ray_hit(t_game *game, const t_ray *ray)
{
	double	hit_x;
	double	hit_y;
	double	max_dist;
	double	dist;

	// Keep the antialiased edge inside the square minimap border.
	max_dist = (MINIMAP_SIZE / 2.0 - 1) / MINIMAP_TILE;
	max_dist /= fmax(fabs(ray->dir_x), fabs(ray->dir_y));
	dist = fmin(ray->perp_dist, max_dist);
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
