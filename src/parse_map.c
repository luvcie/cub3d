/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:56:08 by lucpardo          #+#    #+#             */
/*   Updated: 2025/10/01 14:46:27 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// the map is read twice, once to count and once to store, 4 gud mem allocation
// counts total lines in map file, opens it and counts newlines
// these newline characters are used to know map HEIGHT before allocating
static int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	buffer[1];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	lines = 0;
	while (read(fd, buffer, 1) > 0)
	{
		if (buffer[0] == '\n')
			lines++;
	}
	close(fd);
	return (lines);
}

// allocates memory for the map awway based on map_height
// inits all pointers to NULL for safety
static void	init_map_memory(t_game *game)
{
	int	i;

	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		exit(1);
	i = 0;
	while (i <= game->map_height)
	{
		game->map[i] = NULL;
		i++;
	}
}

// checks if line is a config line (NO/SO/WE/EA/F/C) and parses it
// takes: line string, game struct pointer
// returns: 1 if config line was parsed, 0 if not
// mutates: game texture paths or colors if config line
static int	is_config_line(char *line, t_game *game)
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
		return (0);
	return (1);
}

// checks if line is empty (only whitespace or newline)
// takes: line string
// returns: 1 if empty, 0 if not
static int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

// processes a line from map file, trims newline character with strtrim
// stores trimmed string in map[map_index] and updates map_width
static void	process_line(t_game *game, char *line, int *map_index)
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

// reads entire map file, line by line using GNL
// processes config lines first, then map lines
static void	read_map_lines(char *filename, t_game *game)
{
	int		fd;
	int		map_index;
	int		in_map;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_map_error("could not open file");
	map_index = 0;
	in_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			if (!in_map && is_config_line(line, game))
				;
			else
			{
				in_map = 1;
				process_line(game, line, &map_index);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map_height = map_index;
	close(fd);
}

// main parsing, counts lines to get height and allocates memory
// reads all map lines into array then finds player start position
void	parse_map(char *filename, t_game *game)
{
	validate_extension(filename);
	game->map_height = count_lines(filename);
	if (game->map_height == 0)
		print_map_error("empty file");
	init_map_memory(game);
	read_map_lines(filename, game);
	find_player(game);
	validate_config(game);
	validate_walls(game);
	validate_elements(game);
}
