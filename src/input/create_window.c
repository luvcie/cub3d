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
		mlx_get_screen_size(game->mlx, &w, &h);
		change_resolution(game, w, h);
	}
}

// recreates window at new resolution
// takes: game, width, height
// mutates: destroys old window/image, sets new dimensions, calls create_window
void	change_resolution(t_game *game, int width, int height)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win_width = width;
	game->win_height = height;
	create_window(game);
}

// creates window, image, hooks and starts event loop
// takes: game struct with mlx initialized and dimensions set
// mutates: creates window, image, registers hooks, starts loop
void	create_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height,
			"cub3D");
	game->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_len, &game->endian);
	game->mouse_x = game->win_width / 2;
	game->last_time = 0;
	mlx_loop_hook(game->mlx, render, game);
	mlx_hook(game->win, MLX_KEYPRESS, MLX_KEYPRESSMASK, key_press, game);
	mlx_hook(game->win, MLX_KEYRELEASE, MLX_KEYRELEASEMASK, key_release, game);
	mlx_hook(game->win, MLX_MOTIONNOTIFY, MLX_POINTERMOTIONMASK,
		mouse_move, game);
	mlx_hook(game->win, MLX_DESTROYNOTIFY, MLX_NOEVENTMASK, close_window, game);
	mlx_loop(game->mlx);
}
