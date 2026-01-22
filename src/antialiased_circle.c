/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiased_circle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:24:22 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/22 19:32:11 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// reads a pixel color from the image buffer
// takes: game struct, x, y coords
// returns: color at that position, or 0 if out of bounds
static unsigned int	get_pixel(t_game *game, int x, int y)
{
	char	*src;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return (0);
	src = game->img_data + (y * game->line_len + x * (game->bpp / 8));
	return (*(unsigned int *)src);
}

// blends two colors based on intensity (0-255)
// takes: foreground color, background color, intensity
// returns: blended color
static unsigned int	blend_color(unsigned int fg, unsigned int bg, int intensity)
{
	int	r;
	int	g;
	int	b;

	r = ((fg >> 16 & 0xFF) * intensity + (bg >> 16 & 0xFF) * (255 - intensity)) / 255;
	g = ((fg >> 8 & 0xFF) * intensity + (bg >> 8 & 0xFF) * (255 - intensity)) / 255;
	b = ((fg & 0xFF) * intensity + (bg & 0xFF) * (255 - intensity)) / 255;
	return ((r << 16) | (g << 8) | b);
}

// helper to draw a pixel with antialiased intensity
// takes: game, x, y, color, intensity (0-255)
static void	plot_aa(t_game *game, int x, int y, int color, int intensity)
{
	unsigned int	bg;

	if (intensity <= 0)
		return ;
	if (intensity >= 255)
	{
		put_pixel(game, x, y, color);
		return ;
	}
	bg = get_pixel(game, x, y);
	put_pixel(game, x, y, blend_color(color, bg, intensity));
}

// draws an antialiased line using xiaolin wu's algorithm
// uses fixed-point math (no floats)
// takes: game struct, start x/y, end x/y, color
// mutates: image buffer
void	draw_line_aa(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int	steep;
	int	dx;
	int	dy;
	int	gradient;
	int	y;
	int	tmp;
	int	x;

	steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep)
	{
		tmp = x0; x0 = y0; y0 = tmp;
		tmp = x1; x1 = y1; y1 = tmp;
	}
	if (x0 > x1)
	{
		tmp = x0; x0 = x1; x1 = tmp;
		tmp = y0; y0 = y1; y1 = tmp;
	}
	dx = x1 - x0;
	dy = y1 - y0;
	if (dx == 0)
		gradient = 256;
	else
		gradient = (dy * 256) / dx;
	y = y0 * 256 + 128;
	x = x0;
	while (x <= x1)
	{
		if (steep)
		{
			plot_aa(game, y / 256, x, color, 255 - (y % 256));
			plot_aa(game, y / 256 + 1, x, color, y % 256);
		}
		else
		{
			plot_aa(game, x, y / 256, color, 255 - (y % 256));
			plot_aa(game, x, y / 256 + 1, color, y % 256);
		}
		y += gradient;
		x++;
	}
}

// draws a filled circle with antialiased edges
// uses integer-only math (no floats, no sqrt)
// takes: game struct, center x/y, radius, color
// mutates: image buffer
void	draw_circle_aa(t_game *game, int x0, int y0, int r, int color)
{
	int				x;
	int				y;
	unsigned int	rmin;
	unsigned int	rmax;
	unsigned int	sqd;
	unsigned int	c;
	unsigned int	bg;

	rmin = r * r - r;
	rmax = r * r + r;
	y = y0 - r;
	while (y <= y0 + r)
	{
		x = x0 - r;
		while (x <= x0 + r)
		{
			sqd = (x - x0) * (x - x0) + (y - y0) * (y - y0);
			if (sqd < rmin)
				put_pixel(game, x, y, color);
			else if (sqd < rmax)
			{
				c = (rmax - sqd) * 256 / (2 * r);
				if (c > 255)
					c = 255;
				bg = get_pixel(game, x, y);
				put_pixel(game, x, y, blend_color(color, bg, c));
			}
			x++;
		}
		y++;
	}
}
