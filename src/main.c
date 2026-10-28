/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:07:53 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 02:57:12 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	parse_map(argv[1], &game);
	find_player(&game);
	load_textures(&game);
	game.gfx = gfx_init("cub3D", 0, 0);
	if (!game.gfx)
	{
		printf("Error\nFailed to create window\n");
		free_game(&game);
		return (1);
	}
	init_view(&game);
	game.show_minimap = true;
	game.show_help = true;
	gfx_run(game.gfx, &(t_gfx_hooks){render, key_press, key_release,
		mouse_move, close_window, &game});
	return (0);
}
