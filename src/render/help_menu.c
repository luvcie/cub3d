/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:38:09 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 02:57:26 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// builds resolution string like "current: 1920x1080"
// takes: width, height
// returns: allocated string (caller must free)
static char	*build_res_str(int w, int h)
{
	char	*ws;
	char	*hs;
	char	*tmp;
	char	*res;

	ws = ft_itoa(w);
	hs = ft_itoa(h);
	tmp = ft_strjoin("current: ", ws);
	free(ws);
	ws = ft_strjoin(tmp, "x");
	free(tmp);
	res = ft_strjoin(ws, hs);
	free(ws);
	free(hs);
	return (res);
}

// draws help overlay with controls and resolution info
// takes: game struct
// mutates: draws text directly on window
void	draw_help_menu(t_game *game)
{
	int		x;
	int		y;
	char	*res;

	x = game->win_width - HELP_MENU_WIDTH - HELP_MENU_MARGIN_R;
	y = game->win_height - HELP_MENU_HEIGHT - HELP_MENU_MARGIN_B;
	mlx_string_put(game->mlx, game->win, x, y, 0xFFFFFF, "-- CONTROLS --");
	mlx_string_put(game->mlx, game->win, x, y + 20, 0xCCCCCC, "WASD: move");
	mlx_string_put(game->mlx, game->win, x, y + 40, 0xCCCCCC, "arrows: look");
	mlx_string_put(game->mlx, game->win, x, y + 60, 0xCCCCCC, "mouse: look");
	mlx_string_put(game->mlx, game->win, x, y + 80, 0xCCCCCC, "M: minimap");
	mlx_string_put(game->mlx, game->win, x, y + 100, 0xCCCCCC, "R: ray debug");
	mlx_string_put(game->mlx, game->win, x, y + 120, 0xCCCCCC, "H: this menu");
	mlx_string_put(game->mlx, game->win, x, y + 160, 0xCCCCCC, "ESC: quit");
	mlx_string_put(game->mlx, game->win, x, y + 190, 0xFFFFFF,
		"-- RESOLUTION --");
	mlx_string_put(game->mlx, game->win, x, y + 210, 0xCCCCCC, "1: 800x600");
	mlx_string_put(game->mlx, game->win, x, y + 230, 0xCCCCCC, "2: 1024x768");
	mlx_string_put(game->mlx, game->win, x, y + 250, 0xCCCCCC, "3: 1280x720");
	mlx_string_put(game->mlx, game->win, x, y + 270, 0xCCCCCC, "4: 1366x768");
	mlx_string_put(game->mlx, game->win, x, y + 290, 0xCCCCCC, "5: 1920x1080");
	mlx_string_put(game->mlx, game->win, x, y + 310, 0xCCCCCC, "6: fullscreen");
	res = build_res_str(game->win_width, game->win_height);
	mlx_string_put(game->mlx, game->win, x, y + 340, 0x00FF00, res);
	free(res);
}
