/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:32:18 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/25 23:44:04 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// puts a pixel in the image buffer (fast, no window update)
// takes: game struct, x, y, color
// mutates: modifies pixel at (x, y) in image buffer

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= game->win_width || y < 0 || y >= game->win_height)
		return ;
	dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

// draws a filled rectangle using point and size
// takes: game struct, position point, size, color
// mutates: draws rectangle on the image buffer

void	draw_rect(t_game *game, t_point pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(game, pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}

// clears the entire image buffer to black
// takes: game struct
// mutates: resets all pixels in image buffer to 0
static void	clear_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->win_height * game->line_len)
	{
		game->img_data[i] = 0;
		i++;
	}
}

static long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000L + tv.tv_usec);
}

// draws help overlay with controls and resolution info
// takes: game struct
// mutates: draws text directly on window
static void	draw_help_menu(t_game *game)
{
	int		x;
	int		y;
	char	res[32];

	x = game->win_width - 150;
	y = 30;
	mlx_string_put(game->mlx, game->win, x, y, 0xFFFFFF, "-- CONTROLS --");
	mlx_string_put(game->mlx, game->win, x, y + 20, 0xCCCCCC, "WASD: move");
	mlx_string_put(game->mlx, game->win, x, y + 40, 0xCCCCCC, "arrows: look");
	mlx_string_put(game->mlx, game->win, x, y + 60, 0xCCCCCC, "mouse: look");
	mlx_string_put(game->mlx, game->win, x, y + 80, 0xCCCCCC, "M: minimap");
	mlx_string_put(game->mlx, game->win, x, y + 100, 0xCCCCCC, "R: ray debug");
	mlx_string_put(game->mlx, game->win, x, y + 120, 0xCCCCCC, "H: this menu");
	mlx_string_put(game->mlx, game->win, x, y + 140, 0xCCCCCC, "ESC: quit");
	mlx_string_put(game->mlx, game->win, x, y + 170, 0xFFFFFF, "-- RESOLUTION --");
	mlx_string_put(game->mlx, game->win, x, y + 190, 0xCCCCCC, "1: 800x600");
	mlx_string_put(game->mlx, game->win, x, y + 210, 0xCCCCCC, "2: 1024x768");
	mlx_string_put(game->mlx, game->win, x, y + 230, 0xCCCCCC, "3: 1280x720");
	mlx_string_put(game->mlx, game->win, x, y + 250, 0xCCCCCC, "4: 1366x768");
	mlx_string_put(game->mlx, game->win, x, y + 270, 0xCCCCCC, "5: 1920x1080");
	mlx_string_put(game->mlx, game->win, x, y + 290, 0xCCCCCC, "6: fullscreen");
	sprintf(res, "current: %dx%d", game->win_width, game->win_height);
	mlx_string_put(game->mlx, game->win, x, y + 320, 0x00FF00, res);
}

// main render function called every frame by mlx_loop_hook
// delta_time normalizes to 60 fps: 1.0 at 60fps, 0.5 at 120fps, 2.0 at 30fps
// takes: game struct
// returns: 0
int	render(t_game *game)
{
	long	now;

	now = get_time_us();
	if (game->last_time == 0)
		game->last_time = now;
	game->delta_time = (now - game->last_time) / 1000000.0 * 60.0;
	game->last_time = now;
	process_movement(game);
	clear_image(game);
	render_3d(game);
	if (game->show_minimap)
		draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	if (game->show_help)
		draw_help_menu(game);
	return (0);
}
