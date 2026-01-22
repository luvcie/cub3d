/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:32:11 by lucpardo          #+#    #+#             */
/*   Updated: 2025/10/02 18:41:08 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// prints error message and exits with status 1 when map validation fails
void	print_map_error(char *message)
{
	ft_printf("Error\n%s\n", message);
	exit(1);
}

// checks if file extension is valid
void	validate_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		print_map_error("invalid file name");
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		print_map_error("hey!! file must have .cub extension!");
}

// checks that all config values were set
// takes: game struct pointer
void	validate_config(t_game *game)
{
	if (!game->texture_no)
		print_map_error("missing north texture (NO)");
	if (!game->texture_so)
		print_map_error("missing south texture (SO)");
	if (!game->texture_we)
		print_map_error("missing west texture (WE)");
	if (!game->texture_ea)
		print_map_error("missing east texture (EA)");
}

// gets character at position in map
// takes: game struct pointer, x and y coordinates
// returns: character at position, or space if out of bounds
static char	get_char_at(t_game *game, int x, int y)
{
	int	row_len;

	if (y < 0 || y >= game->map_height)
		return (' ');
	row_len = ft_strlen(game->map[y]);
	if (x < 0 || x >= row_len)
		return (' ');
	return (game->map[y][x]);
}

// checks if character is a floor tile (walkable area)
// takes: character
// returns: 1 if floor, 0 if not
static int	is_floor(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// checks that a floor tile is not adjacent to space or boundary
// cub3d maps can have spaces, but floor tiles must be enclosed by walls
// takes: game struct pointer, x and y coordinates
static void	check_tile_enclosed(t_game *game, int x, int y)
{
	if (get_char_at(game, x - 1, y) == ' ')
		print_map_error("the map must be surrounded by walls you know !!");
	if (get_char_at(game, x + 1, y) == ' ')
		print_map_error("the map must be surrounded by walls you know !!");
	if (get_char_at(game, x, y - 1) == ' ')
		print_map_error("the map must be surrounded by walls you know !!");
	if (get_char_at(game, x, y + 1) == ' ')
		print_map_error("the map must be surrounded by walls you know !!");
}

// validates walls surround the playable area
// in cub3d, floor tiles (0, N, S, E, W) must not touch spaces or boundaries
void	validate_walls(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (is_floor(game->map[y][x]))
				check_tile_enclosed(game, x, y);
		}
	}
}

// helper function to count element types in map
// counts[0] = player positions (N/S/E/W)
void	count_elements(t_game *game, int *counts)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (game->map[y][++x])
		{
			c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				counts[0]++;
			else if (c != '0' && c != '1' && c != ' ')
				print_map_error("invalid character in map D:");
		}
	}
}

// validates element counts: exactly 1 player position (N/S/E/W)
void	validate_elements(t_game *game)
{
	int	counts[1];

	counts[0] = 0;
	count_elements(game, counts);
	if (counts[0] == 0)
		print_map_error("no player position found! need N, S, E or W");
	if (counts[0] > 1)
		print_map_error("too many player positions! only 1 allowed");
}

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
