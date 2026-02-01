/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 22:15:17 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 01:19:48 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// sets up ray direction using camera plane for proper FOV perspective
// cam_x maps screen column to [-1, 1], then rotates by player angle
// takes: game, ray, screen column x
// mutates: ray direction, grid position, sign_x/y computed branchless
void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	cam_x;
	double	dir_x;
	double	dir_y;

	dir_x = cos(game->player_angle);
	dir_y = sin(game->player_angle);
	cam_x = 2 * x / (double)game->win_width - 1;
	ray->dir_x = dir_x + (-dir_y * FOV) * cam_x;
	ray->dir_y = dir_y + (dir_x * FOV) * cam_x;
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;
	ray->sign_x = 1 - 2 * (ray->dir_x < 0);
	ray->sign_y = 1 - 2 * (ray->dir_y < 0);
	ray->side = 0;
}

// draws the textured wall strip with edge blending
// takes: game, ray, screen column x, tex
// mutates: writes wall pixels to image buffer
static void	draw_wall_strip(t_game *game, t_ray *ray, int x, t_tex *tex)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;

	tex_x = (int)(ray->wall_x * tex->width);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = ((y - game->win_height / 2 + ray->line_height / 2)
				* tex->height) / ray->line_height;
		color = get_tex_pixel(tex, tex_x, tex_y);
		if (y == ray->draw_start && ray->draw_start_f >= 0)
			color = blend_color(color, game->ceiling_color,
					(int)((1.0 - (ray->draw_start_f - (int)ray->draw_start_f))
						* 255));
		else if (y == ray->draw_end && ray->draw_end_f < game->win_height)
			color = blend_color(color, game->floor_color,
					(int)((ray->draw_end_f - (int)ray->draw_end_f) * 255));
		put_pixel(game, x, y++, color);
	}
}

// draws one vertical strip: ceiling, textured wall and floor
// takes: game, ray (with wall data), screen column x
// mutates: writes pixels to image buffer
static void	draw_column(t_game *game, t_ray *ray, int x)
{
	int		y;
	t_tex	*tex;

	tex = &game->tex[ray->wall_dir & 3];
	y = 0;
	while (y < ray->draw_start)
		put_pixel(game, x, y++, game->ceiling_color);
	draw_wall_strip(game, ray, x, tex);
	y = ray->draw_end + 1;
	while (y < game->win_height)
		put_pixel(game, x, y++, game->floor_color);
}

// main 3D render loop: casts one ray per screen column
// takes: game
// mutates: fills entire image buffer with 3D view
void	render_3d(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < game->win_width)
	{
		init_ray(game, &ray, x);
		cast_ray(game, &ray);
		calc_wall(game, &ray);
		draw_column(game, &ray, x);
		x++;
	}
}
