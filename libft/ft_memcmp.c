/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:21:34 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/03 21:28:56 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1ptr;
	unsigned char	*s2ptr;
	size_t			i;	

	s1ptr = (unsigned char *)s1;
	s2ptr = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1ptr[i] != s2ptr[i])
		{
			return (s1ptr[i] - s2ptr[i]);
		}
		i++;
	}
	return (0);
}
/*#include <stdio.h>
int	main(void)
{
	char	s1[] = "aaa";
	char	s2[] = "ccc";
	printf("%d\n", ft_memcmp(s1, s2, 3));
	return (0);
}*/
// compares memory areas
