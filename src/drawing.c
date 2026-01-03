#include "cub3d.h"

// draws a triangle using mlx_pixel_put (slow method)
void	draw_triangle_direct(void *mlx, void *win)
{
	int	x;
	int	y;
	int	color;

	color = 0x00FFD1DC;
	y = 100;
	while (y < 300)
	{
		x = 400 - (y - 100);
		while (x < 400 + (y - 100))
		{
			mlx_pixel_put(mlx, win, x, y, color);
			x++;
		}
		y++;
	}
}

// helper to draw a line
static void	draw_line(void *mlx, void *win, int *p1, int *p2, int color)
{
	float	dx;
	float	dy;
	float	steps;
	float	x;
	float	y;
	int		i;

	dx = p2[0] - p1[0];
	dy = p2[1] - p1[1];
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	i = 0;
	x = p1[0];
	y = p1[1];
	while (i <= steps)
	{
		mlx_pixel_put(mlx, win, (int)x, (int)y, color);
		x += dx / steps;
		y += dy / steps;
		i++;
	}
}

// draws a pentagram using mlx_pixel_put
void	draw_pentagram_direct(void *mlx, void *win)
{
	int		points[5][2];
	int		i;
	int		color;
	double	angle;

	color = 0x00FFD1DC;
	i = 0;
	while (i < 5)
	{
		angle = (i * 72 - 90) * M_PI / 180.0;
		points[i][0] = 400 + (int)(150 * cos(angle));
		points[i][1] = 300 + (int)(150 * sin(angle));
		i++;
	}
	draw_line(mlx, win, points[0], points[2], color);
	draw_line(mlx, win, points[2], points[4], color);
	draw_line(mlx, win, points[4], points[1], color);
	draw_line(mlx, win, points[1], points[3], color);
	draw_line(mlx, win, points[3], points[0], color);
}

// helper to put a pixel in the image buffer
static void	put_pixel_img(char *data, int x, int y, int color,
				int line_len, int bpp)
{
	int	offset;

	offset = y * line_len + x * (bpp / 8);
	*(unsigned int *)(data + offset) = color;
}

// draws a triangle using image buffer (fast method)
void	draw_triangle_buffer(void *mlx, void *win)
{
	void	*img;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;
	int		color;

	img = mlx_new_image(mlx, 800, 600);
	data = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	color = 0x00FFD1DC;
	y = 100;
	while (y < 300)
	{
		x = 400 - (y - 100);
		while (x < 400 + (y - 100))
		{
			put_pixel_img(data, x, y, color, line_len, bpp);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}
