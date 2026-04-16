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

// counts total lines in map file for memory allocation
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

// allocates memory for the map array based on map_height
static void	init_map_memory(t_game *game)
{
	int	i;

	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		print_map_error(game, "memory allocation failed");
	i = 0;
	while (i <= game->map_height)
	{
		game->map[i] = NULL;
		i++;
	}
}

// processes a single line during map reading
static void	handle_line(t_game *game, char *line, int *ctx)
{
	if (!is_empty_line(line))
	{
		if (!ctx[1] && is_config_line(line, game))
			;
		else
		{
			if (ctx[2])
				print_map_error(game, "empty line in map content");
			ctx[1] = 1;
			process_map_line(game, line, &ctx[0]);
		}
	}
	else if (ctx[1])
		ctx[2] = 1;
}

// reads entire map file line by line using GNL
static void	read_map_lines(char *filename, t_game *game)
{
	int		fd;
	int		ctx[3];
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_map_error(game, "could not open file");
	ctx[0] = 0;
	ctx[1] = 0;
	ctx[2] = 0;
	line = get_next_line(fd);
	while (line)
	{
		handle_line(game, line, ctx);
		free(line);
		line = get_next_line(fd);
	}
	game->map_height = ctx[0];
	close(fd);
}

// main parsing entry point
void	parse_map(char *filename, t_game *game)
{
	validate_extension(game, filename);
	game->map_height = count_lines(filename);
	if (game->map_height == 0)
		print_map_error(game, "empty file");
	init_map_memory(game);
	read_map_lines(filename, game);
	find_player(game);
	validate_config(game);
	validate_textures(game);
	validate_walls(game);
	validate_elements(game);
}
