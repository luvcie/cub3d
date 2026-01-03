/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:46:51 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/03 20:20:05 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*dstptr;
	const unsigned char	*srcptr;

	dstptr = (unsigned char *)dst;
	srcptr = (const unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (dst);
	if (dstptr > srcptr)
	{
		dstptr += n;
		srcptr += n;
		while (n-- > 0)
			*(--dstptr) = *(--srcptr);
	}
	else
	{
		while (n-- > 0)
			*(dstptr++) = *(srcptr++);
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

	ft_memmove(dst, src, bytes);
	printf("%s \n", dst);
	return (0);
}*/
// copies memory area, handling overlap by 
// going backwards
// n-- while condition uses current value of n
// and then decreases it by 1.
// ex.  n is now 5, and 5 > 0 is true, so
// n is now 4, and 4 > 0 is true, so...
// n is now 3 ...
