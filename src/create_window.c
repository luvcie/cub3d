#include "cub3d.h"

int	create_window(void)
{
	t_game	game;

	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, 800, 600, "cub3D");
	if (!game.win)
		return (1);
	draw_pentagram_direct(game.mlx, game.win);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
