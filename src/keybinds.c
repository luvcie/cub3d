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

// moves player forward in the direction they're facing
// takes: game struct pointer
// mutates: player_x, player_y
static void	move_forward(t_game *game)
{
	game->player_x += cos(game->player_angle) * 0.1;
	game->player_y += sin(game->player_angle) * 0.1;
}

// moves player backward from the direction they're facing
// takes: game struct pointer
// mutates: player_x, player_y
static void	move_backward(t_game *game)
{
	game->player_x -= cos(game->player_angle) * 0.1;
	game->player_y -= sin(game->player_angle) * 0.1;
}

// slides player to the left
// takes: game struct pointer
// mutates: player_x, player_y
static void	move_left(t_game *game)
{
	game->player_x += cos(game->player_angle - M_PI / 2) * 0.1;
	game->player_y += sin(game->player_angle - M_PI / 2) * 0.1;
}

// slides player to the right
// takes: game struct pointer
// mutates: player_x, player_y
static void	move_right(t_game *game)
{
	game->player_x += cos(game->player_angle + M_PI / 2) * 0.1;
	game->player_y += sin(game->player_angle + M_PI / 2) * 0.1;
}

// handles key presses and runs the matching action
// takes: keycode, game struct pointer
// mutates: player state depending on key
// returns: 0
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
		game->player_angle -= 0.15;
	else if (keycode == KEY_RIGHT)
		game->player_angle += 0.15;
	return (0);
}
