/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-c <pramos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:38:15 by pramos-c          #+#    #+#             */
/*   Updated: 2026/01/25 02:32:22 by pramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// returns player angle based on spawn direction
static double	get_player_angle(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	if (c == 'S')
		return (M_PI / 2);
	if (c == 'E')
		return (0);
	return (M_PI);
}

// finds player start position and sets angle
void	find_player(t_game *game)
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
			{
				game->player_x = x + 0.5;
				game->player_y = y + 0.5;
				game->player_angle = get_player_angle(c);
				return ;
			}
		}
	}
}

// extracts path from config line like "NO ./path/to/texture.xpm"
char	*parse_texture_path(t_game *game, char *line)
{
	char	*path;

	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	path = ft_strtrim(line, " \n");
	if (!path || ft_strlen(path) == 0)
		print_map_error(game, "missing texture path");
	return (path);
}
