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

void	draw_help_menu(t_game *game)
{
	int		x;
	int		y;
	char	*res;

	x = game->win_width - HELP_MENU_WIDTH - HELP_MENU_MARGIN_R;
	y = game->win_height - HELP_MENU_HEIGHT - HELP_MENU_MARGIN_B - 8;
	gfx_draw_text(game->gfx, x, y, 0xFFFFFF, "-- CONTROLS --");
	gfx_draw_text(game->gfx, x, y + 20, 0xCCCCCC, "WASD: move");
	gfx_draw_text(game->gfx, x, y + 40, 0xCCCCCC, "arrows: look");
	gfx_draw_text(game->gfx, x, y + 60, 0xCCCCCC, "mouse: look");
	gfx_draw_text(game->gfx, x, y + 80, 0xCCCCCC, "M: minimap");
	gfx_draw_text(game->gfx, x, y + 100, 0xCCCCCC, "TAB: full map");
	gfx_draw_text(game->gfx, x, y + 120, 0xCCCCCC, "R: ray debug");
	gfx_draw_text(game->gfx, x, y + 140, 0xCCCCCC, "H: this menu");
	gfx_draw_text(game->gfx, x, y + 160, 0xCCCCCC, "ESC: quit");
	gfx_draw_text(game->gfx, x, y + 190, 0xFFFFFF, "-- RESOLUTION --");
	gfx_draw_text(game->gfx, x, y + 210, 0xCCCCCC, "1: 800x600");
	gfx_draw_text(game->gfx, x, y + 230, 0xCCCCCC, "2: 1024x768");
	gfx_draw_text(game->gfx, x, y + 250, 0xCCCCCC, "3: 1280x720");
	gfx_draw_text(game->gfx, x, y + 270, 0xCCCCCC, "4: 1366x768");
	gfx_draw_text(game->gfx, x, y + 290, 0xCCCCCC, "5: 1920x1080");
	gfx_draw_text(game->gfx, x, y + 310, 0xCCCCCC, "6: fullscreen");
	res = build_res_str(game->win_width, game->win_height);
	gfx_draw_text(game->gfx, x, y + 340, 0x00FF00, res);
	free(res);
}
