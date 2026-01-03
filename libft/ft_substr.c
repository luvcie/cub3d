/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 02:48:41 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/05 08:45:45 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	slen;

	if (str == NULL)
		return (NULL);
	slen = ft_strlen(str);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, str + start, len + 1);
	return (ptr);
}
/*#include <stdio.h>
int	main(void)
{
	printf("%s \n", ft_substr("when rain drops", 4, 10));
	return (0);
}*/
// allocates and returns a substring from string 's', 
// starting at index 'start' with a maximum length 'len'
