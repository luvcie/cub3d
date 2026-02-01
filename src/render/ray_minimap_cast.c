/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_minimap_cast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:48:55 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 01:19:00 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// fixed-point scale for bresenham integer math
#define BRES_SCALE 0x10000
// err tolerance for corner detection
#define CORNER_EPS 64

// takes: game, cell coords
// returns: true if wall or oob, false if empty
static bool	is_wall_cell(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (true);
	if (x >= (int)ft_strlen(game->map[y]))
		return (true);
	return (game->map[y][x] == '1');
}

// supercover corner handler
// takes: game, ray, err ptr, direction magnitudes
// returns: true if hit wall, false if stepped diagonal safely
static bool	handle_corner(t_game *game, t_ray *ray, long *err, long d[2])
{
	if (is_wall_cell(game, ray->map_x + ray->sign_x, ray->map_y))
	{
		ray->map_x += ray->sign_x;
		ray->side = 0;
		return (true);
	}
	if (is_wall_cell(game, ray->map_x, ray->map_y + ray->sign_y))
	{
		ray->map_y += ray->sign_y;
		ray->side = 1;
		return (true);
	}
	ray->map_x += ray->sign_x;
	ray->map_y += ray->sign_y;
	*err += d[1] - d[0];
	return (false);
}

// computes initial bresenham error
// takes: game, ray, d (scaled direction magnitudes)
// returns: initial err value
static long	init_bresenham_err(t_game *game, t_ray *ray, long d[2])
{
	double	dist[2];

	if (ray->sign_x > 0)
		dist[0] = ray->map_x + 1.0 - game->player_x;
	else
		dist[0] = game->player_x - ray->map_x;
	if (ray->sign_y > 0)
		dist[1] = ray->map_y + 1.0 - game->player_y;
	else
		dist[1] = game->player_y - ray->map_y;
	return ((long)(dist[0] * d[1] - dist[1] * d[0]));
}

// branchless step for minimap ray
// takes: ray, err ptr, d (direction magnitudes)
// mutates: ray position, side, err value
static void	step_ray_minimap(t_ray *ray, long *err, long d[2])
{
	int	go_x;

	go_x = (*err < 0);
	ray->map_x += go_x * ray->sign_x;
	ray->map_y += (1 - go_x) * ray->sign_y;
	ray->side = 1 - go_x;
	*err += go_x * d[1] - (1 - go_x) * d[0];
}

// supercover bresenham grid traversal for minimap rays
// takes: game, ray
// mutates: ray->map_x/y ends on wall cell
void	cast_ray_minimap(t_game *game, t_ray *ray)
{
	long	d[2];
	long	err;
	int		steps;

	d[0] = (long)(fabs(ray->dir_x) * BRES_SCALE);
	d[1] = (long)(fabs(ray->dir_y) * BRES_SCALE);
	err = init_bresenham_err(game, ray, d);
	steps = 0;
	while (!is_wall_cell(game, ray->map_x, ray->map_y) && steps < MAX_DEPTH * 2)
	{
		if (err > -CORNER_EPS && err < CORNER_EPS)
		{
			if (handle_corner(game, ray, &err, d))
				return ;
		}
		else
			step_ray_minimap(ray, &err, d);
		steps++;
	}
}
