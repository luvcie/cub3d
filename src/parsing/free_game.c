/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-c <pramos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:51:08 by pramos-c          #+#    #+#             */
/*   Updated: 2026/01/25 02:46:44 by pramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

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

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		gfx_free_image(game->tex[i]);
		game->tex[i] = NULL;
		i++;
	}
}

void	free_game(t_game *game)
{
	free(game->ray_hits);
	game->ray_hits = NULL;
	free_game_map(game);
	if (game->current_line)
		free(game->current_line);
	if (game->texture_no)
		free(game->texture_no);
	if (game->texture_so)
		free(game->texture_so);
	if (game->texture_we)
		free(game->texture_we);
	if (game->texture_ea)
		free(game->texture_ea);
	free_textures(game);
	gfx_quit(game->gfx);
	game->gfx = NULL;
}
