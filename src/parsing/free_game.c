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
}
