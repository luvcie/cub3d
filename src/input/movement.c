#include "cub3d.h"

// checks if a specific map point is a wall or out of bounds
// takes: game struct, x, y
// returns: 1 if wall/invalid, 0 if safe/empty
static int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	if (!game->map)
		return (0);
	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

// checks if player position is valid (collision with radius)
// takes: game struct, x, y
// returns: 1 if valid, 0 if invalid
static int	is_valid_pos(t_game *game, double x, double y)
{
	if (is_wall(game, x - PLAYER_RADIUS, y - PLAYER_RADIUS))
		return (0);
	if (is_wall(game, x + PLAYER_RADIUS, y - PLAYER_RADIUS))
		return (0);
	if (is_wall(game, x - PLAYER_RADIUS, y + PLAYER_RADIUS))
		return (0);
	if (is_wall(game, x + PLAYER_RADIUS, y + PLAYER_RADIUS))
		return (0);
	return (1);
}

// attempts to move player by dx, dy with collision checks
// takes: game struct, delta x, delta y
// mutates: game->player_x/y if move is valid
static void	try_move(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (is_valid_pos(game, new_x, game->player_y))
		game->player_x = new_x;
	if (is_valid_pos(game, game->player_x, new_y))
		game->player_y = new_y;
}

// processes movement based on currently held keys
// called every frame from render loop
// takes: game struct pointer
// mutates: player position and angle
void	process_movement(t_game *game)
{
	if (game->keys.w)
		try_move(game, cos(game->player_angle) * MOVE_SPEED,
			sin(game->player_angle) * MOVE_SPEED);
	if (game->keys.s)
		try_move(game, -cos(game->player_angle) * MOVE_SPEED,
			-sin(game->player_angle) * MOVE_SPEED);
	if (game->keys.a)
		try_move(game, cos(game->player_angle - M_PI / 2) * MOVE_SPEED,
			sin(game->player_angle - M_PI / 2) * MOVE_SPEED);
	if (game->keys.d)
		try_move(game, cos(game->player_angle + M_PI / 2) * MOVE_SPEED,
			sin(game->player_angle + M_PI / 2) * MOVE_SPEED);
	if (game->keys.left)
		game->player_angle -= ROT_SPEED;
	if (game->keys.right)
		game->player_angle += ROT_SPEED;
}
