#include "cub3d.h"
#include <stdio.h>
#include <math.h>

// mock map
// 111
// 101
// 111
char *mock_map[] = {
	"111",
	"101",
	"111",
	NULL
};

void print_status(t_game *game)
{
	printf("Pos: (%.2f, %.2f)\n", game->player_x, game->player_y);
}

int main(void)
{
	t_game game;
	
ft_memset(&game, 0, sizeof(t_game));
	
	// setup map
	game.map = mock_map;
	game.map_width = 3;
	game.map_height = 3;
	
	// start at center
	game.player_x = 1.5;
	game.player_y = 1.5;
	
	// test 1: move north (up) towards wall
	printf("Test 1: Move North towards wall (Radius: %.2f)\n", PLAYER_RADIUS);
	game.player_angle = -M_PI / 2; // facing up (negative y)
	game.keys.w = true;

	// move multiple steps
	for (int i = 0; i < 50; i++)
	{
		process_movement(&game);
	}

	print_status(&game);

	// with radius 0.2:
	// wall is at y < 1.0.
	// player top edge is y - 0.2.
	// collision if y - 0.2 < 1.0  => y < 1.2.
	// so player should stop at y >= 1.2.

	if (game.player_y < 1.2)
		printf("FAIL: Player too close to wall (y=%.2f, limit=1.2)\n", game.player_y);
	else
		printf("PASS: Player stopped at y=%.2f (>= 1.2)\n", game.player_y);

	// test 2: move east towards wall
	printf("Test 2: Move East towards wall\n");
	game.player_x = 1.5;
	game.player_y = 1.5;
	game.player_angle = 0; // facing east
	game.keys.w = true;
	
	for (int i = 0; i < 50; i++)
	{
		process_movement(&game);
	}
	print_status(&game);
	
	// with radius 0.2:
	// wall is at x >= 2.0.
	// player right edge is x + 0.2.
	// collision if x + 0.2 >= 2.0 => x >= 1.8.
	// so player should stop at x <= 1.8.
	
	if (game.player_x > 1.8 + 0.01) // allow tiny float error
		printf("FAIL: Player too close to wall (x=%.2f, limit=1.8)\n", game.player_x);
	else
		printf("PASS: Player stopped at x=%.2f (<= 1.8)\n", game.player_x);

	return (0);
}