#include "cub3d.h"

// wraps key_press and prints position/angle after each keypress
static int	test_key_press(int keycode, t_game *game)
{
	int	result;

	result = key_press(keycode, game);
	printf("pos: %.2f, %.2f | angle: %.2f\n",
		game->player_x, game->player_y, game->player_angle);
	return (result);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("usage: ./test_minimap <file.cub>\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	parse_map(argv[1], &game);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "minimap test");
	if (!game.win)
		return (1);
	game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	game.img_data = mlx_get_data_addr(game.img, &game.bpp,
			&game.line_len, &game.endian);
	printf("image buffer ready, entering loop...\n");
	fflush(stdout);
	printf("controls: WASD to move, arrows to rotate, ESC to quit\n");
	mlx_loop_hook(game.mlx, (int (*)())render, &game);
	mlx_hook(game.win, 2, 1L << 0, (int (*)())test_key_press, &game);
	mlx_hook(game.win, 17, 0, (int (*)())close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
