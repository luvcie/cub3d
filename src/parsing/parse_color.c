/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:12:01 by lucpardo          #+#    #+#             */
/*   Updated: 2026/04/16 16:27:28 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// frees the array returned by ft_split
static void	free_split(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

// checks that a string is only digits with optional surrounding whitespace
static bool	is_valid_number(char *s)
{
	int		i;
	bool	has_digit;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	has_digit = false;
	while (s[i] >= '0' && s[i] <= '9')
	{
		has_digit = true;
		i++;
	}
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	return (has_digit && s[i] == '\0');
}

// validates all three color components are numeric strings
static void	check_numbers(t_game *game, char **parts)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (!is_valid_number(parts[i]))
		{
			free_split(parts);
			print_map_error(game, "color values must be numeric");
		}
	}
}

// parses RGB color string like "220,100,0" into single int
int	parse_color(t_game *game, char *str)
{
	char	**parts;
	int		rgb[3];

	while (*str == ' ')
		str++;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		if (parts)
			free_split(parts);
		print_map_error(game, "invalid color format");
	}
	check_numbers(game, parts);
	rgb[0] = ft_atoi(parts[0]);
	rgb[1] = ft_atoi(parts[1]);
	rgb[2] = ft_atoi(parts[2]);
	free_split(parts);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
		print_map_error(game, "color values must be 0-255");
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
