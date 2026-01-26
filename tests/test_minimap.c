#include "cub3d.h"

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
	mlx_get_screen_size(game.mlx, &game.win_width, &game.win_height);
	printf("Screen size: %dx%d (aspect: %.2f)\n", game.win_width,
		game.win_height, game.win_width / (double)game.win_height);
	game.win = mlx_new_window(game.mlx, game.win_width, game.win_height,
			"minimap test");
	if (!game.win)
		return (1);
	game.img = mlx_new_image(game.mlx, game.win_width, game.win_height);
	game.img_data = mlx_get_data_addr(game.img, &game.bpp,
			&game.line_len, &game.endian);
	load_textures(&game);
	game.mouse_x = game.win_width / 2;
	printf("controls: WASD to move, arrows/mouse to rotate, ESC to quit\n");
	mlx_loop_hook(game.mlx, (int (*)())render, &game);
	mlx_hook(game.win, 2, 1L << 0, (int (*)())key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, (int (*)())key_release, &game);
	mlx_hook(game.win, 6, 1L << 6, (int (*)())mouse_move, &game);
	mlx_hook(game.win, 17, 0, (int (*)())close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
