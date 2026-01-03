/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:21:02 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/01 22:52:37 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	space;
	size_t	i;
	size_t	j;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen >= size)
		return (size + srclen);
	space = size - dstlen -1;
	i = 0;
	j = dstlen;
	while (src[i] != '\0' && i < space)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (srclen + dstlen);
}

/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	dest[50];
	const char *src;
	size_t	result;
	size_t	box;
	
	strcpy(dest, "put me");
	src = " together";
	box = 35;
	result = ft_strlcat(dest, src, box);
	printf("returns: %zu dest: \"%s\"\n", result, dest);
	return (0);
}*/
