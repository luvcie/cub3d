/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:44:31 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/01 01:17:41 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lilen;

	if (*little == '\0')
		return ((char *)big);
	lilen = ft_strlen(little);
	i = 0;
	while (big[i] != '\0' && i + lilen <= len)
	{
		if (ft_strncmp(big + i, little, lilen) == 0)
		{
			return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strnstr("heat from fire fire from heat", "from fire", 90));
	return (0);
}*/
// locates a substring in the first n bytes of a string
