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

// takes: void *param (cast to t_game)
// mutates: destroys window, frees mlx, exits program
int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

// sets/clears movement key flag based on keycode
// takes: game, keycode, bool value
// mutates: flips flag in game->keys
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

// takes: keycode, void *param (cast to t_game)
// mutates: sets key flags, toggles views, or changes resolution
int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		close_window(param);
	else if (keycode == KEY_R)
		game->show_rays = !game->show_rays;
	else if (keycode == KEY_M)
		game->show_minimap = !game->show_minimap;
	else if (keycode == KEY_H)
		game->show_help = !game->show_help;
	else if (keycode >= KEY_1 && keycode <= KEY_6)
		handle_resolution_keys(keycode, game);
	else
		set_key(game, keycode, true);
	return (0);
}

// takes: keycode, void *param (cast to t_game)
// mutates: clears key flags in game->keys
int	key_release(int keycode, void *param)
{
	set_key((t_game *)param, keycode, false);
	return (0);
}

// takes: x pos, y pos (unused), void *param (cast to t_game)
// mutates: player_angle based on horizontal mouse delta
int	mouse_move(int x, int y, void *param)
{
	t_game	*game;
	int		delta;

	game = (t_game *)param;
	(void)y;
	delta = x - game->mouse_x;
	game->mouse_x = x;
	game->player_angle += delta * 0.003;
	return (0);
}
