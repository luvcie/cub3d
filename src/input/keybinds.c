/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:48:21 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/25 23:43:15 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// takes: game
// mutates: destroys window, frees mlx, exits program
int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

// takes: keycode, game
// mutates: sets key flags in game->keys, R toggles show_rays
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	else if (keycode == KEY_R)
		game->show_rays = !game->show_rays;
	else if (keycode == KEY_M)
		game->show_minimap = !game->show_minimap;
	return (0);
}

// takes: keycode, game
// mutates: clears key flags in game->keys
int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

// takes: x pos, y pos (unused), game
// mutates: player_angle based on horizontal mouse delta
int	mouse_move(int x, int y, t_game *game)
{
	int	delta;

	(void)y;
	delta = x - game->mouse_x;
	game->mouse_x = x;
	game->player_angle += delta * 0.003;
	return (0);
}
