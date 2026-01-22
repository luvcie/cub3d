#include "cub3d.h"

int	create_window(void)
{
	t_game	game;

	game.player_x = 0;
	game.player_y = 0;
	game.player_angle = 0;
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, 800, 600, "cub3D");
	if (!game.win)
		return (1);
	mlx_key_hook(game.win, (int (*)())key_press, &game);
	mlx_hook(game.win, 17, 0, (int (*)())close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
