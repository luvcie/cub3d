/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:41:33 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/26 13:45:33 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// fixed-point scale for bresenham integer math
#define BRES_SCALE 0x10000
// err tolerance for corner detection, catches near-diagonal rays that
// would otherwise slip through wall corners
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

// takes: game, ray, angle in radians
// mutates: ray direction and grid position, sign_x/y computed branchless
// with the 1 - 2*(negative) trick giving +1 or -1
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

// supercover corner handler: when err is near zero the ray passes through
// a grid corner, so we check both adjacent cells before stepping diagonal
// takes: game, ray, err ptr, direction magnitudes
// returns: true if hits a wall, false if stepped diagonal safely
// mutates: ray position/side, err value
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

// computes initial bresenham error: dist_to_x * |dy| - dist_to_y * |dx|
// negative = x boundary closer, positive = y boundary closer
// takes: game, ray, d (scaled direction magnitudes)
// returns: initial err value for the stepping loop
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

// supercover bresenham grid traversal, walks cells til we hit a wall
// the main stepping logic is branchless, go_x selects direction via
// arithmetic (not if/else). corner case when |err| < EPS needs branches
// to check adjacent walls before diagonal step
// takes: game, ray
// mutates: ray->map_x/y ends on wall cell, ray->side set to hit axis
static void	cast_ray_bresenham(t_game *game, t_ray *ray)
{
	long	d[2];
	long	err;
	int		go_x;
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
		{
			go_x = (err < 0);
			ray->map_x += go_x * ray->sign_x;
			ray->map_y += (1 - go_x) * ray->sign_y;
			ray->side = 1 - go_x;
			err += go_x * d[1] - (1 - go_x) * d[0];
		}
		steps++;
	}
}

// perpendicular distance calc, tavianator style - no branches
// picks t[0] or t[1] via array index based on which axis we hit
// the 1e-30 trick prevents div by zero without branching
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
// mutates: draws WIN_WIDTH rays to image buffer
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
		cast_ray_bresenham(game, &ray);
		calc_dist_branchless(game, &ray);
		draw_single_ray(game, &ray);
		i++;
	}
}
