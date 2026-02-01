#include "cub3d.h"

// wraps key_press and prints position/angle after each keypress
// takes: keycode, game struct pointer
// returns: result from key_press
static int	test_key_press(int keycode, t_game *game)
{
	int	result;

	result = key_press(keycode, game);
	printf("pos: %.2f, %.2f | angle: %.2f\n",
		game->player_x, game->player_y, game->player_angle);
	return (result);
}

int	main(void)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	game.player_x = 0;
	game.player_y = 0;
	game.player_angle = 0;
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win_width = 800;
	game.win_height = 600;
	game.win = mlx_new_window(game.mlx, game.win_width, game.win_height,
			"cub3D - movement test");
	if (!game.win)
		return (1);
	printf("movement test started\n");
	printf("controls: WASD to move, arrows to rotate, ESC to quit\n");
	mlx_key_hook(game.win, (int (*)())test_key_press, &game);
	mlx_hook(game.win, MLX_DESTROYNOTIFY, MLX_NOEVENTMASK, (int (*)())close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
