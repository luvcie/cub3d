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

void	put_pixel(t_game *game, int x, int y, int color)
{
	if (x < 0 || x >= game->win_width || y < 0 || y >= game->win_height)
		return ;
	game->frame->pixels[y * game->frame->w + x] = color;
}

static long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000L + tv.tv_usec);
}

// delta_time normalizes to 60 fps: 1.0 at 60fps, 0.5 at 120fps, 2.0 at 30fps
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
	render_3d(game);
	if (game->show_minimap)
		draw_minimap(game);
}

void	draw_overlay(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->show_help)
		draw_help_menu(game);
}
