#include "cub3d.h"

// draws inner solid pixel of circle
static void	draw_solid_pixel(t_game *game, t_point p, int color)
{
	put_pixel(game, p.x, p.y, color);
}

// draws antialiased edge pixel of circle
static void	draw_edge_pixel(t_game *game, t_point p, int color, int intensity)
{
	int	bg;

	if (intensity > 255)
		intensity = 255;
	bg = get_pixel_color(game, p.x, p.y);
	put_pixel(game, p.x, p.y, blend_color(color, bg, intensity));
}

// calculates intensity for edge pixel
static int	calc_intensity(unsigned int rmax, unsigned int sqd, int r)
{
	return ((rmax - sqd) * 256 / (2 * r));
}

// draws one row of the circle
static void	draw_circle_row(t_game *game, t_point c, int *params, int y)
{
	int				x;
	unsigned int	sqd;
	t_point			p;

	x = c.x - params[0];
	while (x <= c.x + params[0])
	{
		sqd = (x - c.x) * (x - c.x) + (y - c.y) * (y - c.y);
		p = (t_point){x, y};
		if (sqd < (unsigned int)params[1])
			draw_solid_pixel(game, p, params[3]);
		else if (sqd < (unsigned int)params[2])
			draw_edge_pixel(game, p, params[3],
				calc_intensity(params[2], sqd, params[0]));
		x++;
	}
}

// draws a filled circle with antialiased edges
void	draw_circle_aa(t_game *game, t_point center, int r, int color)
{
	int	y;
	int	params[4];

	params[0] = r;
	params[1] = r * r - r;
	params[2] = r * r + r;
	params[3] = color;
	y = center.y - r;
	while (y <= center.y + r)
	{
		draw_circle_row(game, center, params, y);
		y++;
	}
}
