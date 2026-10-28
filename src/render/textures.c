/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 22:12:33 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 01:20:11 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// loads bmp textures for walls (N/S/E/W mapped to tex[0-3])
// takes: game
// mutates: game->tex array with image pixels and dimensions
void	load_textures(t_game *game)
{
	game->tex[0] = gfx_load_bmp(game->texture_no);
	game->tex[1] = gfx_load_bmp(game->texture_so);
	game->tex[2] = gfx_load_bmp(game->texture_ea);
	game->tex[3] = gfx_load_bmp(game->texture_we);
	if (!game->tex[0] || !game->tex[1]
		|| !game->tex[2] || !game->tex[3])
	{
		printf("Error\nFailed to load textures\n");
		free_game(game);
		exit(1);
	}
}

// samples a pixel from texture data, with bounds checking
// takes: texture image, x/y coords in texture space
// returns: color at that position, or 0 if oob
int	get_tex_pixel(t_image *tex, int x, int y)
{
	if (x < 0 || x >= tex->w || y < 0 || y >= tex->h)
		return (0);
	return ((int)tex->pixels[y * tex->w + x]);
}
