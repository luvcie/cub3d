/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:53:15 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/01 21:15:45 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		++i;
	}
	if ((unsigned char)c == '\0')
	{
		return ((char *)str + i);
	}
	i = i - 1;
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
		{
			return ((char *)str + i);
		}
		--i;
	}
	return (NULL);
}

/*#include <stdio.h>*/
/*int		main(void)
{
	printf("%s \n", ft_strrchr("banana", 'a'));
	printf("%s \n", ft_strrchr("ukelele", 'e'));
	return (0);
}*/
// returns a pointer to the last occurrence of the character c in the string s
