/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:48:54 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/02 14:00:36 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char	*s)
{
	size_t	i;
	char	*dest;
	size_t	inputstrlen;

	i = 0;
	inputstrlen = ft_strlen(s);
	dest = (char *)malloc(inputstrlen + 1);
	if (dest == NULL)
	{
		return (NULL);
	}
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*#include <stdio.h>
int	main(void)
{
	printf("duplicated string: %s \n", ft_strdup("hello"));
	return (0);
}*/
