#include "cub3d.h"

int create_window() 
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 800, 600, "cub3D");
	if (!win)
		return (1);
	mlx_loop(mlx);
	return (0);
}
