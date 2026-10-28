/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:32:18 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 01:28:05 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// puts a pixel in the frame buffer (fast, shown after render returns)
// takes: game struct, x, y, color
// mutates: modifies pixel at (x, y) in frame buffer
void	put_pixel(t_game *game, int x, int y, int color)
{
	if (x < 0 || x >= game->win_width || y < 0 || y >= game->win_height)
		return ;
	game->frame->pixels[y * game->frame->w + x] = color;
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

// clears the entire frame buffer to black
// takes: game struct
// mutates: resets all pixels in frame buffer to 0
static void	clear_image(t_game *game)
{
	ft_memset(game->frame->pixels, 0,
		game->frame->w * game->frame->h * sizeof(uint32_t));
}

static long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000L + tv.tv_usec);
}

// main render function called every frame by gfx_run
// delta_time normalizes to 60 fps: 1.0 at 60fps, 0.5 at 120fps, 2.0 at 30fps
// takes: void *param (cast to t_game)
void	render(void *param)
{
	t_game	*game;
	long	now;

	game = (t_game *)param;
	game->frame = gfx_frame(game->gfx);
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
	if (game->show_help)
		draw_help_menu(game);
}
