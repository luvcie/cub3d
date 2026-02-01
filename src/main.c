/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:07:53 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/31 18:54:04 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	main(void)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	mlx_get_screen_size(game.mlx, &game.win_width, &game.win_height);
	create_window(&game);
	return (0);
}
