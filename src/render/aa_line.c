/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:18:06 by lucpardo          #+#    #+#             */
/*   Updated: 2026/01/25 02:33:24 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// swaps two integer values
// takes: pointer to integer a, pointer to integer b
// mutates: swaps the values of a and b
static void	swap_int(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// draws a pixel with antialiased intensity
// takes: game struct, point p, color, intensity (0-255)
// mutates: blends and sets pixel at (p.x, p.y)
static void	plot_aa(t_game *game, t_point p, int color, int intensity)
{
	int	bg;

	if (intensity <= 0)
		return ;
	if (intensity >= 255)
	{
		put_pixel(game, p.x, p.y, color);
		return ;
	}
	bg = get_pixel_color(game, p.x, p.y);
	put_pixel(game, p.x, p.y, blend_color(color, bg, intensity));
}

// draws two pixels for current position (steep or normal)
// takes: game struct, color, coords array, steep flag
// mutates: draws two pixels for the line segment
static void	draw_aa_pixels(t_game *game, int color, int *coords, int steep)
{
	t_point	p;

	if (steep)
		p = (t_point){coords[1] / 256, coords[0]};
	else
		p = (t_point){coords[0], coords[1] / 256};
	plot_aa(game, p, color, 255 - (coords[1] % 256));
	if (steep)
		p = (t_point){coords[1] / 256 + 1, coords[0]};
	else
		p = (t_point){coords[0], coords[1] / 256 + 1};
	plot_aa(game, p, color, coords[1] % 256);
}

// prepares line for drawing (ensures left-to-right, handles steep)
// takes: pointer to line struct
// mutates: modifies line coordinates if necessary
// returns: steep flag (1 if steep, 0 otherwise)
static int	prepare_line(t_line *ln)
{
	int	steep;

	steep = abs(ln->p1.y - ln->p0.y) > abs(ln->p1.x - ln->p0.x);
	if (steep)
	{
		swap_int(&ln->p0.x, &ln->p0.y);
		swap_int(&ln->p1.x, &ln->p1.y);
	}
	if (ln->p0.x > ln->p1.x)
	{
		swap_int(&ln->p0.x, &ln->p1.x);
		swap_int(&ln->p0.y, &ln->p1.y);
	}
	return (steep);
}

// draws an antialiased line using xiaolin wu's algorithm
// takes: game struct, line struct
// mutates: draws line on the image buffer
void	draw_line_aa(t_game *game, t_line line)
{
	int	steep;
	int	dx;
	int	gradient;
	int	coords[2];

	steep = prepare_line(&line);
	dx = line.p1.x - line.p0.x;
	if (dx == 0)
		gradient = 256;
	else
		gradient = ((line.p1.y - line.p0.y) * 256) / dx;
	coords[1] = line.p0.y * 256 + 128;
	coords[0] = line.p0.x;
	while (coords[0] <= line.p1.x)
	{
		draw_aa_pixels(game, line.color, coords, steep);
		coords[1] += gradient;
		coords[0]++;
	}
}
