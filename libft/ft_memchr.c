/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:18:00 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 17:51:43 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)ptr[i] == (unsigned char)c)
		{
			return ((void *)(ptr + i));
		}
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	const char *search = "When the sunlight strikes raindrops in the air.";
	int	tofind;	
	size_t	bytes;
	void	*found;

	tofind = 's';
	bytes = 30;

	found = ft_memchr(search, tofind, bytes);
	printf("\n you found '%c' at %p ! :D", tofind, found);

	return (0);
}*/
