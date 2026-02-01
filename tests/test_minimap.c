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
	load_textures(&game);
	printf("controls: WASD to move, arrows/mouse to rotate, ESC to quit\n");
	create_window(&game);
	return (0);
}
