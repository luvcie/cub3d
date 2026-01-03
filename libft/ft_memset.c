/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:14:19 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/02 17:11:08 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/* #include <stdio.h>
int	main(void)
{
	char	str[20];

	ft_memset(str, 'O', 19);
	str[19] = '\0';
	printf("%s \n", str);
	return (0);
}*/
// fills first n bytes of memory area pointed by s
// with the constant byte c
