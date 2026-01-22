#include "cub3d.h"

// test parsing by printing all parsed values
int	main(int argc, char **argv)
{
	t_game	game;
	int		i;

	if (argc != 2)
	{
		printf("usage: ./test_parsing <file.cub>\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	parse_map(argv[1], &game);
	printf("------ parsed config ------\n");
	printf("NO: %s\n", game.texture_no);
	printf("SO: %s\n", game.texture_so);
	printf("WE: %s\n", game.texture_we);
	printf("EA: %s\n", game.texture_ea);
	printf("floor: 0x%06X\n", game.floor_color);
	printf("ceiling: 0x%06X\n", game.ceiling_color);
	printf("\n------ parsed map ------\n");
	printf("size: %d x %d\n", game.map_width, game.map_height);
	i = 0;
	while (i < game.map_height)
	{
		printf("[%s]\n", game.map[i]);
		i++;
	}
	printf("\n------ player ------\n");
	printf("pos: %.2f, %.2f\n", game.player_x, game.player_y);
	printf("angle: %.2f rad\n", game.player_angle);
	free_game(&game);
	return (0);
}
