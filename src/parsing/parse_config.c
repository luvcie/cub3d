/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-c <pramos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:23:41 by pramos-c          #+#    #+#             */
/*   Updated: 2026/01/25 02:31:58 by pramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// checks if line is a config line (NO/SO/WE/EA/F/C) and parses it
// returns: true if config line was parsed, false if not
bool	is_config_line(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->texture_no = parse_texture_path(line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->texture_so = parse_texture_path(line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->texture_we = parse_texture_path(line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->texture_ea = parse_texture_path(line);
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->floor_color = parse_color(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->ceiling_color = parse_color(line + 2);
	else
		return (false);
	return (true);
}

// checks if line is empty (only whitespace or newline)
bool	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

// processes a map line, trims newline and stores in map array
void	process_map_line(t_game *game, char *line, int *map_index)
{
	int	len;

	game->map[*map_index] = ft_strtrim(line, "\n");
	if (!game->map[*map_index])
		print_map_error("memory allocation failed");
	len = ft_strlen(game->map[*map_index]);
	if (len > game->map_width)
		game->map_width = len;
	(*map_index)++;
}
