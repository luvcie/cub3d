/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 22:08:45 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/28 02:47:32 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// fixed-point scale for bresenham integer math
#define BRES_SCALE 0x10000
// err tolerance for corner detection, catches near-diagonal rays that
// would otherwise slip through wall corners
#define CORNER_EPS 64

// loads xpm textures for walls (N/S/E/W mapped to tex[0-3])
// takes: game
// mutates: game->tex array with image data and dimensions
void	load_textures(t_game *game)
{
	int	i;

	game->tex[0].img = mlx_xpm_file_to_image(game->mlx, game->texture_no,
			&game->tex[0].width, &game->tex[0].height);
	game->tex[1].img = mlx_xpm_file_to_image(game->mlx, game->texture_so,
			&game->tex[1].width, &game->tex[1].height);
	game->tex[2].img = mlx_xpm_file_to_image(game->mlx, game->texture_ea,
			&game->tex[2].width, &game->tex[2].height);
	game->tex[3].img = mlx_xpm_file_to_image(game->mlx, game->texture_we,
			&game->tex[3].width, &game->tex[3].height);
	if (!game->tex[0].img || !game->tex[1].img
		|| !game->tex[2].img || !game->tex[3].img)
	{
		printf("Error\nFailed to load textures\n");
		free_textures(game);
		free_game(game);
		exit(1);
	}
	i = -1;
	while (++i < 4)
	{
		game->tex[i].data = mlx_get_data_addr(game->tex[i].img,
				&game->tex[i].bpp, &game->tex[i].line_len, &game->tex[i].endian);
		if (!game->tex[i].data)
		{
			printf("Error\nFailed to get texture data\n");
			free_textures(game);
			free_game(game);
			exit(1);
		}
	}
}

// takes: game, cell coords
// returns: true if wall or oob, false if passable
static bool	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (true);
	if (x >= (int)ft_strlen(game->map[y]))
		return (true);
	return (game->map[y][x] == '1');
}

// sets up ray direction using camera plane for proper FOV perspective
// cam_x maps screen column to [-1, 1], then rotates by player angle
// takes: game, ray, screen column x
// mutates: ray direction, grid position, sign_x/y computed branchless
static void	init_ray(t_game *game, t_ray *ray, int x)
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

// supercover corner handler: when err is near zero the ray passes through
// a grid corner, so we check both adjacent cells before stepping diagonal
// takes: game, ray, err ptr, direction magnitudes
// returns: true if hit wall, false if stepped diagonal safely
// mutates: ray position/side, err value
static bool	handle_corner(t_game *game, t_ray *ray, long *err, long d[2])
{
	if (is_wall(game, ray->map_x + ray->sign_x, ray->map_y))
	{
		ray->map_x += ray->sign_x;
		ray->side = 0;
		return (true);
	}
	if (is_wall(game, ray->map_x, ray->map_y + ray->sign_y))
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
static long	init_err(t_game *game, t_ray *ray, long d[2])
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
static void	cast_ray(t_game *game, t_ray *ray)
{
	long	d[2];
	long	err;
	int		go_x;
	int		steps;

	d[0] = (long)(fabs(ray->dir_x) * BRES_SCALE);
	d[1] = (long)(fabs(ray->dir_y) * BRES_SCALE);
	err = init_err(game, ray, d);
	steps = 0;
	while (!is_wall(game, ray->map_x, ray->map_y) && steps < MAX_DEPTH * 2)
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

// perpendicular distance calc, tavianator style without branches
// picks t[0] or t[1] via array index based on which axis we hit
// the 1e-30 trick prevents div by zero without branching
// also computes wall_x (fractional hit position) for texture mapping
// takes: game, ray (after traversal)
// mutates: ray->perp_dist, wall_x, wall_dir, line_height, draw bounds
static void	calc_wall(t_game *game, t_ray *ray)
{
	double	t[2];
	double	denom[2];

	denom[0] = ray->dir_x + (ray->dir_x == 0) * 1e-30;
	denom[1] = ray->dir_y + (ray->dir_y == 0) * 1e-30;
	t[0] = (ray->map_x - game->player_x + (1 - ray->sign_x) * 0.5) / denom[0];
	t[1] = (ray->map_y - game->player_y + (1 - ray->sign_y) * 0.5) / denom[1];
	ray->perp_dist = t[ray->side];
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
	if (ray->perp_dist < 0.0001)
		ray->perp_dist = 0.0001;
	ray->line_height = (int)(game->win_height / ray->perp_dist);
	if (ray->line_height < 1)
		ray->line_height = 1;
	ray->draw_start = game->win_height / 2 - ray->line_height / 2;
	ray->draw_end = game->win_height / 2 + ray->line_height / 2;
	ray->draw_start_f = (game->win_height - (double)game->win_height / ray->perp_dist) / 2.0;
	ray->draw_end_f = (game->win_height + (double)game->win_height / ray->perp_dist) / 2.0;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
}

// samples a pixel from texture data, with bounds checking
// takes: texture struct, x/y coords in texture space
// returns: color at that position, or 0 if oob
static int	get_tex_pixel(t_tex *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->data + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}

// draws one vertical strip: ceiling, textured wall and floor
// blends top and bottom pixels to have smooth edges
// takes: game, ray (with wall data), screen column x
// mutates: writes pixels to image buffer
static void	draw_column(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		tex_x;
	int		tex_y;
	t_tex	*tex;

	tex = &game->tex[ray->wall_dir & 3];
	tex_x = (int)(ray->wall_x * tex->width);
	y = 0;
	while (y < ray->draw_start)
		put_pixel(game, x, y++, game->ceiling_color);
	if (y <= ray->draw_end)
	{
		tex_y = ((y - game->win_height / 2 + ray->line_height / 2)
				* tex->height) / ray->line_height;
		int color = get_tex_pixel(tex, tex_x, tex_y);
		if (ray->draw_start_f >= 0)
		{
			double coverage = 1.0 - (ray->draw_start_f - floor(ray->draw_start_f));
			color = blend_color(color, game->ceiling_color, (int)(coverage * 255));
		}
		put_pixel(game, x, y++, color);
	}
	while (y < ray->draw_end)
	{
		tex_y = ((y - game->win_height / 2 + ray->line_height / 2)
				* tex->height) / ray->line_height;
		put_pixel(game, x, y++, get_tex_pixel(tex, tex_x, tex_y));
	}
	if (y == ray->draw_end)
	{
		tex_y = ((y - game->win_height / 2 + ray->line_height / 2)
				* tex->height) / ray->line_height;
		int color = get_tex_pixel(tex, tex_x, tex_y);
		if (ray->draw_end_f < game->win_height)
		{
			double coverage = ray->draw_end_f - floor(ray->draw_end_f);
			color = blend_color(color, game->floor_color, (int)(coverage * 255));
		}
		put_pixel(game, x, y++, color);
	}
	while (y < game->win_height)
		put_pixel(game, x, y++, game->floor_color);
}

// main 3D render loop: casts one ray per screen column
// same bresenham algorithm as minimap, but output is textured wall strips
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
