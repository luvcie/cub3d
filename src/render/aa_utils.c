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

int	get_pixel_color(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->win_width || y < 0 || y >= game->win_height)
		return (0);
	return ((int)game->frame->pixels[y * game->frame->w + x]);
}

static int	blend_channel(int fg_ch, int bg_ch, int intensity)
{
	return ((fg_ch * intensity + bg_ch * (255 - intensity)) / 255);
}

// Intensity 0 selects the background; 255 selects the foreground.
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
