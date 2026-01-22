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

// prints error message and exits with status 1
void	print_map_error(char *message)
{
	ft_printf("Error\n%s\n", message);
	exit(1);
}

// checks if file extension is valid (.cub)
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

// counts player positions and validates characters
static void	count_elements(t_game *game, int *counts)
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

// validates element counts: exactly 1 player position
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
