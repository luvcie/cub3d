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

// loads texture images from xpm files
// takes: game
// mutates: game->tex[0-3].img, width, height
static void	load_texture_images(t_game *game)
{
	game->tex[0].img = mlx_xpm_file_to_image(game->mlx, game->texture_no,
			&game->tex[0].width, &game->tex[0].height);
	game->tex[1].img = mlx_xpm_file_to_image(game->mlx, game->texture_so,
			&game->tex[1].width, &game->tex[1].height);
	game->tex[2].img = mlx_xpm_file_to_image(game->mlx, game->texture_ea,
			&game->tex[2].width, &game->tex[2].height);
	game->tex[3].img = mlx_xpm_file_to_image(game->mlx, game->texture_we,
			&game->tex[3].width, &game->tex[3].height);
	if (!game->tex[0].img || !game->tex[1].img
		|| !game->tex[2].img || !game->tex[3].img)
	{
		printf("Error\nFailed to load textures\n");
		free_game(game);
		exit(1);
	}
}

// loads xpm textures for walls (N/S/E/W mapped to tex[0-3])
// takes: game
// mutates: game->tex array with image data and dimensions
void	load_textures(t_game *game)
{
	int	i;

	load_texture_images(game);
	i = -1;
	while (++i < 4)
	{
		game->tex[i].data = mlx_get_data_addr(game->tex[i].img,
				&game->tex[i].bpp, &game->tex[i].line_len,
				&game->tex[i].endian);
		if (!game->tex[i].data)
		{
			printf("Error\nFailed to get texture data\n");
			free_textures(game);
			free_game(game);
			exit(1);
		}
	}
}

// samples a pixel from texture data, with bounds checking
// takes: texture struct, x/y coords in texture space
// returns: color at that position, or 0 if oob
int	get_tex_pixel(t_tex *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->data + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}
