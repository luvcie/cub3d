#include "cub3d.h"
#include <assert.h>

static void test_line_precision(void)
{
	t_game game = {0};
	game.win_width = 128;
	game.win_height = 128;
	game.frame = gfx_new_image(128, 128);
	assert(game.frame);
	draw_line_aa(&game, (t_line){{20, 40}, {100, 40}, 0xFFFFFF});
	assert(get_pixel_color(&game, 60, 40) == 0xFFFFFF);
	assert(get_pixel_color(&game, 60, 41) == 0);
	memset(game.frame->pixels, 0, 128 * 128 * sizeof(uint32_t));
	draw_line_aa(&game, (t_line){{20, 40.25}, {100, 40.25}, 0xFFFFFF});
	assert(get_pixel_color(&game, 60, 40) == 0xBFBFBF);
	assert(get_pixel_color(&game, 60, 41) == 0x404040);
	memset(game.frame->pixels, 0, 128 * 128 * sizeof(uint32_t));
	draw_line_aa(&game, (t_line){{40.25, 100}, {40.25, 20}, 0xFFFFFF});
	assert(get_pixel_color(&game, 40, 60) == 0xBFBFBF);
	assert(get_pixel_color(&game, 41, 60) == 0x404040);
	gfx_free_image(game.frame);
}

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
	game->map_mode = MAP_MINI;
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
	t_point start = game->minimap.pos;
	t_point end = {start.x + game->minimap.size,
		start.y + game->minimap.size};

	for (int y = 0; y < game->win_height; y++)
		for (int x = 0; x < game->win_width; x++)
			if (x < start.x || x > end.x || y < start.y || y > end.y)
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

static void assert_marker_aligned(t_game *game, t_point_f origin, t_ray ray)
{
	bool steep = fabs(ray.dir_y) > fabs(ray.dir_x);
	double major = steep ? origin.y : origin.x;
	double minor = steep ? origin.x : origin.y;
	double dir_major = steep ? ray.dir_y : ray.dir_x;
	double dir_minor = steep ? ray.dir_x : ray.dir_y;
	int sample = (int)round(major) + (dir_major > 0 ? 8 : -8);
	double expected = minor + (sample - major) * dir_minor / dir_major;
	double total = 0;
	double weighted = 0;

	for (int pixel = (int)floor(expected) - 2;
		pixel <= (int)ceil(expected) + 2; pixel++)
	{
		int color = get_pixel_color(game, steep ? pixel : sample,
			steep ? sample : pixel);
		int red = (color >> 16) & 255;
		int green = (color >> 8) & 255;
		int blue = color & 255;
		int weight = red - (int)fmax(green, blue) - 8;
		if (weight > 0)
		{
			total += weight;
			weighted += weight * pixel;
		}
	}
	assert(total > 0);
	assert(fabs(weighted / total - expected) < 0.08);
}

static void test_player_marker(t_game *game)
{
	t_point_f center = world_to_minimap(game, game->player_x, game->player_y);

	for (int visible = 0; visible < 2; visible++)
	{
		render(game);
		memset(game->frame->pixels, 0,
			(size_t)game->win_width * game->win_height * sizeof(uint32_t));
		draw_minimap(game);
		for (int edge = 0; edge < 2; edge++)
		{
			t_ray ray;
			init_ray(game, &ray, edge * (game->win_width - 1));
			assert_marker_aligned(game, center, ray);
		}
		key_press(KEY_R, game);
	}
}

static void assert_full_map_fits(t_game *game)
{
	t_minimap_view *view = &game->minimap;
	t_point_f first = world_to_minimap(game, 0, 0);
	t_point_f last = world_to_minimap(game, game->map_width, game->map_height);

	assert(view->pos.x >= 0 && view->pos.y >= 0);
	assert(view->pos.x + view->size < game->win_width);
	assert(view->pos.y + view->size < game->win_height);
	assert(abs(2 * view->pos.x + view->size - game->win_width) <= 1);
	assert(abs(2 * view->pos.y + view->size - game->win_height) <= 1);
	assert(first.x > view->pos.x && first.y > view->pos.y);
	assert(last.x < view->pos.x + view->size);
	assert(last.y < view->pos.y + view->size);
	t_point_f player = world_to_minimap(game, game->player_x, game->player_y);
	assert(get_pixel_color(game, player.x, player.y) == 0xFF0000);
}

static void test_full_map(t_game *game)
{
	change_resolution(game, 800, 600);
	game->player_x = 20.5;
	game->player_y = 20.5;
	game->player_angle = 0;
	game->map_mode = MAP_HIDDEN;
	render(game);
	uint32_t *without_map = snapshot(game);
	key_press(KEY_TAB, game);
	assert(game->map_mode == MAP_FULL);
	render(game);
	assert_full_map_fits(game);
	assert(game->minimap.size > MINIMAP_SIZE);
	assert_outside_unchanged(game, without_map);
	for (int y = 0; y < 2; y++)
		for (int x = 0; x < 2; x++)
		{
			t_point_f corner = world_to_minimap(game, x * 40 + 0.5,
				y * 40 + 0.5);
			assert(get_pixel_color(game, corner.x, corner.y)
				!= (int)without_map[(int)corner.y * game->win_width
					+ (int)corner.x]);
		}
	free(without_map);
	uint32_t *without_rays = snapshot(game);
	key_press(KEY_R, game);
	render(game);
	t_point_f visible = world_to_minimap(game, 23, 21.75);
	t_point_f hidden = world_to_minimap(game, 26, 23.25);
	assert(((get_pixel_color(game, visible.x, visible.y) >> 16) & 255) > 128);
	assert(get_pixel_color(game, hidden.x, hidden.y)
		== (int)without_rays[(int)hidden.y * game->win_width + (int)hidden.x]);
	assert_outside_unchanged(game, without_rays);
	key_press(KEY_R, game);
	free(without_rays);
	struct timeval now;
	gettimeofday(&now, NULL);
	game->last_time = now.tv_sec * 1000000L + now.tv_usec - 16667;
	key_press(KEY_W, game);
	key_press(KEY_RIGHT, game);
	render(game);
	key_release(KEY_W, game);
	key_release(KEY_RIGHT, game);
	assert(game->player_x > 20.5 && game->player_angle > 0);
	assert(game->map_mode == MAP_FULL);
	key_press(KEY_TAB, game);
	assert(game->map_mode == MAP_MINI);
	render(game);
	assert(game->minimap.size == MINIMAP_SIZE);
	key_press(KEY_TAB, game);
	key_press(KEY_M, game);
	assert(game->map_mode == MAP_HIDDEN);
	key_press(KEY_M, game);
	assert(game->map_mode == MAP_MINI);
	game->screensaver = true;
	key_press(KEY_TAB, game);
	assert(game->map_mode == MAP_MINI);
	game->screensaver = false;
}

static void test_level_maps(void)
{
	const char *maps[] = {"maps/test.cub", "maps/test_big.cub", "maps/maze.cub",
		"maps/pillars.cub", "maps/corridor.cub", "maps/ivory.cub", "maps/iris.cub"};

	for (size_t i = 0; i < sizeof(maps) / sizeof(*maps); i++)
	{
		t_game game = {0};
		parse_map((char *)maps[i], &game);
		load_textures(&game);
		game.gfx = gfx_init("full map test", 800, 600);
		assert(game.gfx);
		init_view(&game);
		key_press(KEY_TAB, &game);
		key_press(KEY_R, &game);
		for (int size = 0; size < 3; size++)
		{
			change_resolution(&game, 320 + 800 * size, 240 + 400 * size);
			render(&game);
			assert_full_map_fits(&game);
			key_press(KEY_R, &game);
			for (int direction = 0; direction < 8; direction++)
			{
				game.player_angle = direction * M_PI / 4;
				test_player_marker(&game);
			}
			key_press(KEY_R, &game);
		}
		free_game(&game);
	}
}

int main(void)
{
	t_game game = {0};
	int widths[] = {320, 800, 1920};
	int heights[] = {240, 600, 1080};

	test_line_precision();
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
		for (int direction = 0; direction < 8; direction++)
		{
			game.player_angle = direction * M_PI / 4 + 0.137;
			test_player_marker(&game);
		}
	}
	test_full_map(&game);
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
	test_level_maps();
	puts("Map views, rays, player markers, movement and controls passed");
}
