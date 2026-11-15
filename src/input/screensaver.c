#include "cub3d.h"

static bool	walkable(t_game *game, int x, int y)
{
	char	cell;

	if (y < 0 || y >= game->map_height || x < 0
		|| x >= (int)ft_strlen(game->map[y]))
		return (false);
	cell = game->map[y][x];
	return (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W');
}

static void	choose_target(t_game *game)
{
	const int	dx[] = {1, 0, -1, 0};
	const int	dy[] = {0, 1, 0, -1};
	int			options[4];
	int			count;
	int			dir;
	int			x;
	int			y;

	x = (int)game->player_x;
	y = (int)game->player_y;
	count = 0;
	dir = -1;
	while (++dir < 4)
		if (walkable(game, x + dx[dir], y + dy[dir])
			&& (!game->screensaver_target
				|| dir != (game->screensaver_direction + 2) % 4))
			options[count++] = dir;
	if (count == 0 && game->screensaver_target)
		options[count++] = (game->screensaver_direction + 2) % 4;
	if (count == 0)
		return ;
	dir = options[rand() % count];
	game->screensaver_direction = dir;
	game->screensaver_x = x + dx[dir] + 0.5;
	game->screensaver_y = y + dy[dir] + 0.5;
	game->screensaver_target = true;
}

void	screensaver_step(t_game *game)
{
	double	delta;
	double	angle;
	double	distance;
	double	step;

	delta = fmin(game->delta_time, 3.0);
	if (!game->screensaver_target || (game->player_x == game->screensaver_x
			&& game->player_y == game->screensaver_y))
		choose_target(game);
	if (!game->screensaver_target)
	{
		game->player_angle += 0.025 * delta;
		return ;
	}
	angle = atan2(game->screensaver_y - game->player_y,
			game->screensaver_x - game->player_x);
	angle = remainder(angle - game->player_angle, 2 * M_PI);
	step = 0.035 * delta;
	if (fabs(angle) > step)
	{
		game->player_angle += copysign(step, angle);
		return ;
	}
	game->player_angle += angle;
	distance = hypot(game->screensaver_x - game->player_x,
			game->screensaver_y - game->player_y);
	step = fmin(0.035 * delta, distance);
	game->player_x += cos(game->player_angle) * step;
	game->player_y += sin(game->player_angle) * step;
	if (step == distance)
	{
		game->player_x = game->screensaver_x;
		game->player_y = game->screensaver_y;
	}
}
