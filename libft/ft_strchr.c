/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:09:41 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/03 23:08:29 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
		{
			return ((char *)str + i);
		}
		++i;
	}
	if (str[i] == '\0' && (unsigned char)c == '\0')
	{
		return ((char *)str + i);
	}
	return (NULL);
}

/*#include <stdio.h>
int	main(void)
{
	printf("%s \n", ft_strchr("hello", 'o'));
	return (0);
}*/
