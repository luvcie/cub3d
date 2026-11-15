/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:31:42 by lucpardo          #+#    #+#             */
/*   Updated: 2026/04/16 16:48:19 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// Opening a directory can succeed; reading it fails with EISDIR.
static void	check_texture_path(t_game *game, char *path, char *msg)
{
	int		fd;
	char	c;
	int		n;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_map_error(game, msg);
	n = read(fd, &c, 1);
	close(fd);
	if (n <= 0)
		print_map_error(game, msg);
}

void	validate_textures(t_game *game)
{
	check_texture_path(game, game->texture_no, "cannot read NO texture");
	check_texture_path(game, game->texture_so, "cannot read SO texture");
	check_texture_path(game, game->texture_we, "cannot read WE texture");
	check_texture_path(game, game->texture_ea, "cannot read EA texture");
}
