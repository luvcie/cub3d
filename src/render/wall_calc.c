/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 22:18:42 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 01:19:18 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// computes wall hit position and direction for texture mapping
// takes: game, ray
// mutates: ray->wall_x, ray->wall_dir
static void	calc_wall_hit(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->wall_x = game->player_y + ray->perp_dist * ray->dir_y;
		ray->wall_dir = (ray->sign_x > 0) * WALL_WEST
			+ (ray->sign_x < 0) * WALL_EAST;
	}
	else
	{
		ray->wall_x = game->player_x + ray->perp_dist * ray->dir_x;
		ray->wall_dir = (ray->sign_y > 0) * WALL_NORTH
			+ (ray->sign_y < 0) * WALL_SOUTH;
	}
	ray->wall_x -= (int)ray->wall_x;
}

// perpendicular distance calc and draw bounds
// takes: game, ray (after traversal)
// mutates: ray perp_dist, wall_x, wall_dir, line_height, draw bounds
void	calc_wall(t_game *game, t_ray *ray)
{
	double	t[2];
	double	d[2];

	d[0] = ray->dir_x + (ray->dir_x == 0) * 1e-30;
	d[1] = ray->dir_y + (ray->dir_y == 0) * 1e-30;
	t[0] = (ray->map_x - game->player_x + (1 - ray->sign_x) * 0.5) / d[0];
	t[1] = (ray->map_y - game->player_y + (1 - ray->sign_y) * 0.5) / d[1];
	ray->perp_dist = t[ray->side];
	calc_wall_hit(game, ray);
	if (ray->perp_dist < 0.0001)
		ray->perp_dist = 0.0001;
	ray->line_height = (int)(game->win_height / ray->perp_dist);
	if (ray->line_height < 1)
		ray->line_height = 1;
	ray->draw_start = game->win_height / 2 - ray->line_height / 2;
	ray->draw_end = game->win_height / 2 + ray->line_height / 2;
	ray->draw_start_f = (game->win_height
			- (double)game->win_height / ray->perp_dist) / 2.0;
	ray->draw_end_f = (game->win_height
			+ (double)game->win_height / ray->perp_dist) / 2.0;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
}
