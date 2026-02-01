/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:41:33 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 01:28:16 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// takes: game, ray, angle in radians
// mutates: ray direction and grid position
static void	init_ray_angle(t_game *game, t_ray *ray, double angle)
{
	ray->dir_x = cos(angle);
	ray->dir_y = sin(angle);
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;
	ray->sign_x = 1 - 2 * (ray->dir_x < 0);
	ray->sign_y = 1 - 2 * (ray->dir_y < 0);
	ray->side = 0;
}

// perpendicular distance calc
// takes: game, ray (after traversal)
// mutates: ray->perp_dist
static void	calc_dist_branchless(t_game *game, t_ray *ray)
{
	double	t[2];
	double	denom[2];

	denom[0] = ray->dir_x + (ray->dir_x == 0) * 1e-30;
	denom[1] = ray->dir_y + (ray->dir_y == 0) * 1e-30;
	t[0] = (ray->map_x - game->player_x + (1 - ray->sign_x) * 0.5) / denom[0];
	t[1] = (ray->map_y - game->player_y + (1 - ray->sign_y) * 0.5) / denom[1];
	ray->perp_dist = t[ray->side];
}

// takes: game, ray (with perp_dist computed)
// mutates: draws off-white aa line from player to wall hit point
static void	draw_single_ray(t_game *game, t_ray *ray)
{
	t_line	line;
	double	hit_x;
	double	hit_y;

	line.p0.x = (int)(game->player_x * TILE_SIZE);
	line.p0.y = (int)(game->player_y * TILE_SIZE);
	hit_x = game->player_x + ray->dir_x * ray->perp_dist;
	hit_y = game->player_y + ray->dir_y * ray->perp_dist;
	line.p1.x = (int)(hit_x * TILE_SIZE);
	line.p1.y = (int)(hit_y * TILE_SIZE);
	line.color = 0xF0EAD6;
	draw_line_aa(game, line);
}

// casts one ray per screen column across the FOV and draws em on minimap
// takes: game
// mutates: draws rays to image buffer
void	draw_rays_minimap(t_game *game)
{
	t_ray	ray;
	double	angle;
	double	start_angle;
	double	angle_step;
	int		i;

	start_angle = game->player_angle - FOV / 2;
	angle_step = FOV / game->win_width;
	i = 0;
	while (i < game->win_width)
	{
		angle = start_angle + i * angle_step;
		init_ray_angle(game, &ray, angle);
		cast_ray_minimap(game, &ray);
		calc_dist_branchless(game, &ray);
		draw_single_ray(game, &ray);
		i++;
	}
}
