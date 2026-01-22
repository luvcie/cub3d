#include "cub3d.h"

// iterates through entire map array to find player's start position (N/S/E/W)
// stores coords in game->player_x and game->player_y
// also sets player_angle based on direction. called once during map parsing.
void	find_player(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player_x = x + 0.5;
				game->player_y = y + 0.5;
				if (c == 'N')
					game->player_angle = 3 * M_PI / 2;
				else if (c == 'S')
					game->player_angle = M_PI / 2;
				else if (c == 'E')
					game->player_angle = 0;
				else if (c == 'W')
					game->player_angle = M_PI;
				return ;
			}
			x++;
		}
		y++;
	}
}

// parses RGB color string like "220,100,0" into single int
// takes: string with comma-separated RGB values
// returns: color as 0xRRGGBB
int	parse_color(char *str)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	while (*str == ' ')
		str++;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
		print_map_error("invalid color format");
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		print_map_error("color values must be 0-255");
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return ((r << 16) | (g << 8) | b);
}

// extracts path from config line like "NO ./path/to/texture.xpm"
// takes: config line string
// returns: allocated string with just the path
char	*parse_texture_path(char *line)
{
	char	*path;

	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	path = ft_strtrim(line, " \n");
	if (!path || ft_strlen(path) == 0)
		print_map_error("missing texture path");
	return (path);
}
