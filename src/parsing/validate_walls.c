/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 08:02:33 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/25 02:32:43 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// gets character at position in map, returns space if out of bounds
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
static int	is_floor(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// checks that a floor tile is not adjacent to space or boundary
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
