/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:47:37 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/01 19:39:04 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (size == 0)
	{
		return (srclen);
	}
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

/*#include <stdio.h>
int	main(void)
{
	char	dest[500];
	const char * source;
	size_t result;

	source = "wow look at this string";
	printf("ft_strlcpy(dest, \"%s\", 5)\n", source);
	result = ft_strlcpy(dest, source, 5);
	printf("returns: %zu\n", result);
	printf("dest buffer content: \"%s\"\n", dest);
	return (0);
}*/
