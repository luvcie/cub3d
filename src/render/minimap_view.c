#include "cub3d.h"

void	update_minimap_view(t_game *game)
{
	t_minimap_view	*view;

	view = &game->minimap;
	view->pos = (t_point){MINIMAP_MARGIN, MINIMAP_MARGIN};
	view->size = MINIMAP_SIZE;
	view->scale = MINIMAP_TILE;
	view->world_x = game->player_x;
	view->world_y = game->player_y;
	if (game->map_mode == MAP_FULL)
	{
		view->size = (int)fmin(game->win_width, game->win_height) * 3 / 4;
		view->pos.x = (game->win_width - view->size) / 2;
		view->pos.y = (game->win_height - view->size) / 2;
		view->scale = (view->size - 4.0 * MINIMAP_MARGIN)
			/ fmax(game->map_width, game->map_height);
		view->world_x = game->map_width / 2.0;
		view->world_y = game->map_height / 2.0;
	}
}

t_point	world_to_minimap(t_game *game, double wx, double wy)
{
	t_minimap_view	*view;
	t_point			result;

	view = &game->minimap;
	result.x = view->pos.x + view->size / 2
		+ (int)((wx - view->world_x) * view->scale);
	result.y = view->pos.y + view->size / 2
		+ (int)((wy - view->world_y) * view->scale);
	return (result);
}
