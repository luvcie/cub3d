#include "cub3d.h"
#include <assert.h>

static void setup(t_game *game, bool inner_walls)
{
	game->map_width = 41;
	game->map_height = 41;
	game->map = ft_calloc(42, sizeof(char *));
	assert(game->map);
	for (int y = 0; y < 41; y++)
	{
		game->map[y] = ft_calloc(42, sizeof(char));
		assert(game->map[y]);
		for (int x = 0; x < 41; x++)
		{
			bool wall = x == 0 || y == 0 || x == 40 || y == 40;
			if (inner_walls && x >= 16 && x <= 24 && y >= 16 && y <= 24)
				wall = x == 16 || x == 24 || y == 16 || y == 24;
			game->map[y][x] = '0' + wall;
		}
	}
	game->player_x = 20.5;
	game->player_y = 20.5;
	game->floor_color = 0x123456;
	game->ceiling_color = 0x654321;
	game->show_minimap = true;
	for (int i = 0; i < 4; i++)
	{
		game->tex[i] = gfx_new_image(1, 1);
		assert(game->tex[i]);
		game->tex[i]->pixels[0] = 0x800000 + i * 0x002000;
	}
	game->gfx = gfx_init("minimap test", 320, 240);
	assert(game->gfx);
	init_view(game);
}

static uint32_t *snapshot(t_game *game)
{
	size_t size = (size_t)game->win_width * game->win_height * sizeof(uint32_t);
	uint32_t *pixels = malloc(size);

	assert(pixels);
	memcpy(pixels, game->frame->pixels, size);
	return (pixels);
}

static void assert_outside_unchanged(t_game *game, uint32_t *before)
{
	int end = MINIMAP_MARGIN + MINIMAP_SIZE;

	for (int y = 0; y < game->win_height; y++)
		for (int x = 0; x < game->win_width; x++)
			if (x < MINIMAP_MARGIN || x > end
				|| y < MINIMAP_MARGIN || y > end)
				assert(game->frame->pixels[y * game->win_width + x]
					== before[y * game->win_width + x]);
}

static void test_fov(t_game *game, int direction)
{
	int dx[] = {1, 0, -1, 0};
	int dy[] = {0, 1, 0, -1};
	int center = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	uint32_t *before;

	game->player_angle = direction * M_PI / 2;
	render(game);
	before = snapshot(game);
	key_press(KEY_R, game);
	render(game);
	for (int side = -1; side <= 1; side += 2)
	{
		int x = center + 30 * dx[direction] - side * 15 * dy[direction];
		int y = center + 30 * dy[direction] + side * 15 * dx[direction];
		assert(before[y * game->win_width + x] == 0x333333);
		assert(((get_pixel_color(game, x, y) >> 16) & 255) > 128);
		x = center + 66 * dx[direction] - side * 33 * dy[direction];
		y = center + 66 * dy[direction] + side * 33 * dx[direction];
		assert(get_pixel_color(game, x, y) == 0x333333);
	}
	assert_outside_unchanged(game, before);
	key_press(KEY_R, game);
	render(game);
	assert(memcmp(before, game->frame->pixels,
		(size_t)game->win_width * game->win_height * sizeof(uint32_t)) == 0);
	free(before);
}

static void test_clipping(t_game *game)
{
	uint32_t *before;
	int near_edge[] = {MINIMAP_MARGIN + 5,
		MINIMAP_MARGIN + MINIMAP_SIZE - 5};

	for (int direction = 0; direction < 4; direction++)
	{
		game->player_angle = M_PI / 4 + direction * M_PI / 2;
		render(game);
		before = snapshot(game);
		key_press(KEY_R, game);
		render(game);
		int x = near_edge[direction == 0 || direction == 3];
		int y = near_edge[direction < 2];
		bool lit = false;
		for (int dy = -1; dy <= 1; dy++)
			for (int dx = -1; dx <= 1; dx++)
				lit |= ((get_pixel_color(game, x + dx, y + dy) >> 16)
						& 255) > 128;
		assert(lit);
		assert_outside_unchanged(game, before);
		key_press(KEY_R, game);
		free(before);
	}
}

int main(void)
{
	t_game game = {0};
	int widths[] = {320, 800, 1920};
	int heights[] = {240, 600, 1080};

	setup(&game, true);
	for (int size = 0; size < 3; size++)
	{
		key_press(KEY_R, &game);
		change_resolution(&game, widths[size], heights[size]);
		render(&game);
		key_press(KEY_R, &game);
		game.player_x = 20.25 + size * 0.25;
		game.player_y = 20.75 - size * 0.25;
		for (int direction = 0; direction < 4; direction++)
			test_fov(&game, direction);
	}
	key_press(KEY_M, &game);
	render(&game);
	uint32_t *before = snapshot(&game);
	key_press(KEY_R, &game);
	render(&game);
	assert(memcmp(before, game.frame->pixels,
		(size_t)game.win_width * game.win_height * sizeof(uint32_t)) == 0);
	free(before);
	free_game(&game);
	memset(&game, 0, sizeof(game));
	setup(&game, false);
	test_clipping(&game);
	free_game(&game);
	puts("Minimap rays: field of view, wall occlusion, clipping and toggles passed");
}
