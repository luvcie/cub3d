/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:51:08 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/25 02:46:44 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// frees the game map array
void	free_game_map(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (game->map[i])
			free(game->map[i++]);
		free(game->map);
	}
}

// frees loaded texture images from mlx
// takes: game
// mutates: destroys all texture images in game->tex array
void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
		i++;
	}
}

// frees all allocated game resources
void	free_game(t_game *game)
{
	free_game_map(game);
	if (game->texture_no)
		free(game->texture_no);
	if (game->texture_so)
		free(game->texture_so);
	if (game->texture_we)
		free(game->texture_we);
	if (game->texture_ea)
		free(game->texture_ea);
	if (game->mlx)
		free_textures(game);
}
