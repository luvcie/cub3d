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

static void	swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

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

static void	draw_aa_pixels(t_game *game, int color, t_point_f at,
		int steep, double coverage)
{
	t_point	p;
	double	fraction;

	fraction = at.y - floor(at.y);
	if (steep)
		p = (t_point){floor(at.y), at.x};
	else
		p = (t_point){at.x, floor(at.y)};
	plot_aa(game, p, color, lround(255 * (1 - fraction) * coverage));
	if (steep)
		p.x++;
	else
		p.y++;
	plot_aa(game, p, color, lround(255 * fraction * coverage));
}

static int	prepare_line(t_line *ln)
{
	int	steep;

	steep = fabs(ln->p1.y - ln->p0.y) > fabs(ln->p1.x - ln->p0.x);
	if (steep)
	{
		swap_double(&ln->p0.x, &ln->p0.y);
		swap_double(&ln->p1.x, &ln->p1.y);
	}
	if (ln->p0.x > ln->p1.x)
	{
		swap_double(&ln->p0.x, &ln->p1.x);
		swap_double(&ln->p0.y, &ln->p1.y);
	}
	return (steep);
}

// draws an antialiased line using xiaolin wu's algorithm
void	draw_line_aa(t_game *game, t_line line)
{
	int		steep;
	double	dx;
	double	gradient;
	double	coverage;
	t_point_f	at;

	steep = prepare_line(&line);
	dx = line.p1.x - line.p0.x;
	if (dx == 0)
		return ;
	gradient = (line.p1.y - line.p0.y) / dx;
	at.x = floor(line.p0.x + 0.5);
	while (at.x <= floor(line.p1.x + 0.5))
	{
		at.y = line.p0.y + (at.x - line.p0.x) * gradient;
		coverage = fmin(at.x + 0.5, line.p1.x)
			- fmax(at.x - 0.5, line.p0.x);
		draw_aa_pixels(game, line.color, at, steep, coverage);
		at.x++;
	}
}
