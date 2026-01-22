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
	game.win = mlx_new_window(game.mlx, 800, 600, "minimap test");
	if (!game.win)
		return (1);
	draw_minimap(&game);
	mlx_key_hook(game.win, (int (*)())key_press, &game);
	mlx_hook(game.win, 17, 0, (int (*)())close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
