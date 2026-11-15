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

static void	set_texture(t_game *game, char **dst, char *line)
{
	if (*dst)
		print_map_error(game, "duplicate texture identifier");
	*dst = parse_texture_path(game, line);
}

static void	set_color(t_game *game, int *dst, bool *set, char *line)
{
	if (*set)
		print_map_error(game, "duplicate color identifier");
	*dst = parse_color(game, line + 2);
	*set = true;
}

bool	is_config_line(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_texture(game, &game->texture_no, line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_texture(game, &game->texture_so, line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_texture(game, &game->texture_we, line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_texture(game, &game->texture_ea, line);
	else if (ft_strncmp(line, "F ", 2) == 0)
		set_color(game, &game->floor_color, &game->floor_set, line);
	else if (ft_strncmp(line, "C ", 2) == 0)
		set_color(game, &game->ceiling_color, &game->ceiling_set, line);
	else
		return (false);
	return (true);
}

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

void	process_map_line(t_game *game, char *line, int *map_index)
{
	int	len;

	game->map[*map_index] = ft_strtrim(line, "\n");
	if (!game->map[*map_index])
		print_map_error(game, "memory allocation failed");
	len = ft_strlen(game->map[*map_index]);
	if (len > game->map_width)
		game->map_width = len;
	(*map_index)++;
}
