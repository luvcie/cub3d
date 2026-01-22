#include "cub3d.h"

// destroys window and exits the program
// takes: game struct pointer
// returns: 0 (never reached due to exit)
int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

// sets key state to pressed
// takes: keycode, game struct pointer
// mutates: game->keys
// returns: 0
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

// sets key state to released
// takes: keycode, game struct pointer
// mutates: game->keys
// returns: 0
int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

// handles mouse movement for rotation
// takes: x position, y position (unused), game struct pointer
// mutates: player_angle based on horizontal mouse delta
// returns: 0
int	mouse_move(int x, int y, t_game *game)
{
	int	delta;

	(void)y;
	delta = x - game->mouse_x;
	game->mouse_x = x;
	game->player_angle += delta * 0.003;
	return (0);
}
