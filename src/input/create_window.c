/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:12:33 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/31 18:53:24 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

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
	mlx_loop_hook(game->mlx, (int (*)())render, game);
	mlx_hook(game->win, MLX_KEYPRESS, MLX_KEYPRESSMASK, (int (*)())key_press, game);
	mlx_hook(game->win, MLX_KEYRELEASE, MLX_KEYRELEASEMASK, (int (*)())key_release, game);
	mlx_hook(game->win, MLX_MOTIONNOTIFY, MLX_POINTERMOTIONMASK, (int (*)())mouse_move, game);
	mlx_hook(game->win, MLX_DESTROYNOTIFY, MLX_NOEVENTMASK, (int (*)())close_window, game);
	mlx_loop(game->mlx);
}
