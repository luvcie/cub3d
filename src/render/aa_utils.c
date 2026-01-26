/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:04:52 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/26 13:45:12 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// reads a pixel color from the image buffer
// takes: game struct, x, y coords
// returns: color at that position, or 0 if out of bounds
int	get_pixel_color(t_game *game, int x, int y)
{
	char	*src;

	if (x < 0 || x >= game->win_width || y < 0 || y >= game->win_height)
		return (0);
	src = game->img_data + (y * game->line_len + x * (game->bpp / 8));
	return (*(unsigned int *)src);
}

// blends a single color channel
// takes: fg channel, bg channel, intensity
// returns: blended channel value
static int	blend_channel(int fg_ch, int bg_ch, int intensity)
{
	return ((fg_ch * intensity + bg_ch * (255 - intensity)) / 255);
}

// blends two colors based on intensity (0-255)
// takes: foreground color, background color, intensity
// returns: blended color
int	blend_color(int fg, int bg, int intensity)
{
	int	r;
	int	g;
	int	b;

	r = blend_channel((fg >> 16) & 0xFF, (bg >> 16) & 0xFF, intensity);
	g = blend_channel((fg >> 8) & 0xFF, (bg >> 8) & 0xFF, intensity);
	b = blend_channel(fg & 0xFF, bg & 0xFF, intensity);
	return ((r << 16) | (g << 8) | b);
}
