/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-c <pramos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:12:33 by pramos-c          #+#    #+#             */
/*   Updated: 2026/01/31 18:53:24 by pramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// handles resolution preset keys 1-6
// takes: keycode, game
// mutates: changes window/image resolution if key matches
void	handle_resolution_keys(int keycode, t_game *game)
{
	int	w;
	int	h;

	if (keycode == KEY_1)
		change_resolution(game, 800, 600);
	else if (keycode == KEY_2)
		change_resolution(game, 1024, 768);
	else if (keycode == KEY_3)
		change_resolution(game, 1280, 720);
	else if (keycode == KEY_4)
		change_resolution(game, 1366, 768);
	else if (keycode == KEY_5)
		change_resolution(game, 1920, 1080);
	else if (keycode == KEY_6)
	{
		gfx_screen_size(game->gfx, &w, &h);
		change_resolution(game, w, h);
	}
}

// resizes the window and resets the view state
// takes: game, width, height
// mutates: window size, frame, win_width/height, mouse_x, last_time
void	change_resolution(t_game *game, int width, int height)
{
	if (gfx_resize(game->gfx, width, height))
		init_view(game);
}

// takes the frame and size from gfx and resets the view state
// does not start the event loop, gfx_run does that
// takes: game struct with gfx initialized
// mutates: frame, win_width/height, mouse_x, last_time
void	init_view(t_game *game)
{
	game->frame = gfx_frame(game->gfx);
	game->win_width = game->frame->w;
	game->win_height = game->frame->h;
	game->mouse_x = game->win_width / 2;
	game->last_time = 0;
}
