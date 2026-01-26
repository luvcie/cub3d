/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:12:33 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/26 12:42:10 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// recreates window and image buffer at new resolution
// takes: game, width, height
// mutates: destroys old window/image, creates new ones, re-registers hooks
void	change_resolution(t_game *game, int width, int height)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	game->win_width = width;
	game->win_height = height;
	game->win = mlx_new_window(game->mlx, width, height, "cub3D");
	game->img = mlx_new_image(game->mlx, width, height);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_len, &game->endian);
	game->mouse_x = width / 2;
	mlx_hook(game->win, 2, 1L << 0, (int (*)())key_press, game);
	mlx_hook(game->win, 3, 1L << 1, (int (*)())key_release, game);
	mlx_hook(game->win, 6, 1L << 6, (int (*)())mouse_move, game);
	mlx_hook(game->win, 17, 0, (int (*)())close_window, game);
}

int	create_window(void)
{
	t_game	game;

	game.player_x = 0;
	game.player_y = 0;
	game.player_angle = 0;
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	mlx_get_screen_size(game.mlx, &game.win_width, &game.win_height);
	game.win = mlx_new_window(game.mlx, game.win_width, game.win_height,
			"cub3D");
	if (!game.win)
		return (1);
	mlx_key_hook(game.win, (int (*)())key_press, &game);
	mlx_hook(game.win, 17, 0, (int (*)())close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
