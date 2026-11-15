/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-c <pramos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:48:21 by pramos-c          #+#    #+#             */
/*   Updated: 2026/01/31 18:53:53 by pramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	close_window(void *param)
{
	free_game((t_game *)param);
	exit(0);
}

static void	set_key(t_game *game, int keycode, bool val)
{
	if (keycode == KEY_W)
		game->keys.w = val;
	else if (keycode == KEY_S)
		game->keys.s = val;
	else if (keycode == KEY_A)
		game->keys.a = val;
	else if (keycode == KEY_D)
		game->keys.d = val;
	else if (keycode == KEY_LEFT)
		game->keys.left = val;
	else if (keycode == KEY_RIGHT)
		game->keys.right = val;
}

void	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		close_window(param);
	else if (game->screensaver)
		return ;
	else if (keycode == KEY_R)
		game->show_rays = !game->show_rays;
	else if (keycode == KEY_M)
		game->show_minimap = !game->show_minimap;
	else if (keycode == KEY_H)
		game->show_help = !game->show_help;
	else if (keycode >= (int)KEY_1 && keycode <= (int)KEY_6)
		handle_resolution_keys(keycode, game);
	else
		set_key(game, keycode, true);
}

void	key_release(int keycode, void *param)
{
	set_key((t_game *)param, keycode, false);
}

void	mouse_move(int x, int y, void *param)
{
	t_game	*game;
	int		delta;

	game = (t_game *)param;
	(void)y;
	if (game->screensaver)
		return ;
	delta = x - game->mouse_x;
	game->mouse_x = x;
	game->player_angle += delta * 0.003;
}
