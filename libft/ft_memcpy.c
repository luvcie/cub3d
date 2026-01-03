/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:47:37 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/03 18:16:01 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dstptr;
	unsigned char	*srcptr;

	if (n == 0)
		return (dst);
	if (dst == src)
		return (dst);
	dstptr = (unsigned char *)dst;
	srcptr = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dstptr[i] = srcptr[i];
		i++;
	}
	return (dst);
}
/*#include <stdio.h>

int	main(void)
{
	char	src[] = "hewwowworld";
	char	dst[20];
	size_t	bytes;

	bytes = ft_strlen(src) + 1;

	ft_memcpy(dst, src, bytes);
	printf("%s \n", dst);
	return (0);
}*/
// copies a memory area
