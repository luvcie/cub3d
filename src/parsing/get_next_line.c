/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:28:50 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 23:23:01 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif

static int	refill_buffer(int fd, char *buffer, int *pos)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	*pos = 0;
	return (bytes_read);
}

static int	read_char(int fd, char *buffer, int *pos, int *bytes_read)
{
	if (*pos >= *bytes_read)
	{
		*bytes_read = refill_buffer(fd, buffer, pos);
		if (*bytes_read <= 0)
			return (-1);
	}
	return (buffer[(*pos)++]);
}

// static vars maintain state between calls for same fd
static int	build_line(int fd, char *line)
{
	static char	buffer[BUFFER_SIZE];
	static int	pos;
	static int	bytes_read;
	int			i;
	int			c;

	i = 0;
	while (1)
	{
		c = read_char(fd, buffer, &pos, &bytes_read);
		if (c == -1)
			break ;
		line[i] = c;
		if (line[i++] == '\n')
			break ;
		if (i >= BUFFER_SIZE - 1)
			break ;
	}
	line[i] = '\0';
	return (i);
}

// reads one line from fd including newline if present
char	*get_next_line(int fd)
{
	char	line[BUFFER_SIZE];
	int		len;

	if (fd < 0)
		return (NULL);
	len = build_line(fd, line);
	if (len == 0)
		return (NULL);
	return (ft_strdup(line));
}
