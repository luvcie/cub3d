/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:41:38 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/05 11:55:28 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	i;
	size_t	k;

	if (s1 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	i = 0;
	k = s1_len;
	while (i < s1_len && ft_strchr(set, s1[i]))
		i++;
	while (k > i && ft_strchr(set, s1[k - 1]))
		k--;
	if (i >= k)
		return (ft_strdup(""));
	else
		return (ft_substr(s1, i, k - i));
}
/*#include <stdio.h>
int	main(void)
{
	printf("%s \n", ft_strtrim("plsdonttrimme", "trimme"));
	return (0);
}*/
// s1 : string to trim
// set : string containing set of characters to rm
// returns copy of s1 with characters from set removed
