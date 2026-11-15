#include "cub3d.h"
#include <assert.h>

static void run(char **map, int width, int height, int start_x, int start_y,
	int minimum_tiles)
{
	t_game game = {0};
	bool visited[32][32] = {{false}};
	int tiles = 0;

	game.map = map;
	game.map_width = width;
	game.map_height = height;
	game.player_x = start_x + 0.5;
	game.player_y = start_y + 0.5;
	for (int i = 0; i < 100000; i++)
	{
		game.delta_time = (i % 997 == 0) ? 1000 : 1;
		screensaver_step(&game);
		int x = (int)game.player_x;
		int y = (int)game.player_y;
		assert(x >= 0 && x < width && y >= 0 && y < height);
		assert(map[y][x] != '1');
		for (int dx = -1; dx <= 1; dx += 2)
			for (int dy = -1; dy <= 1; dy += 2)
			{
				int cx = (int)(game.player_x + dx * PLAYER_RADIUS);
				int cy = (int)(game.player_y + dy * PLAYER_RADIUS);
				assert(cx >= 0 && cx < width && cy >= 0 && cy < height);
				assert(map[cy][cx] != '1');
			}
		if (!visited[y][x])
		{
			visited[y][x] = true;
			tiles++;
		}
	}
	assert(tiles >= minimum_tiles);
}

int main(void)
{
	char *maze[] = {"1111111", "1000101", "1010101", "1010001",
		"1111111"};
	char *isolated[] = {"111", "101", "111"};

	run(maze, 7, 5, 1, 1, 10);
	run(isolated, 3, 3, 1, 1, 1);
}
