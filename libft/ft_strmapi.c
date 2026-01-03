/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:45:46 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/05 16:39:11 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	str = malloc(sizeof(char) * (s_len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*#include <stdio.h>
#include <ctype.h>
char	ft_rot13(unsigned int i, char c)
{
	if (isupper(c))
	{
		return ((c - 'A' + 13) % 26 + 'A');
	}
	if (islower(c))
	{
		return ((c - 'a' + 13) % 26 + 'a');
	}
	return (c);
}

int	main(void)
{
	char	*result = ft_strmapi("hello world", ft_rot13);
	printf("%s\n", result);
	free(result);
	return (0);
}*/
// s: The string to iterate over.
// f: The function to apply to each character.
// return: The string created from the successive applications of ’f’. 
// Returns NULL if the allocation fails.
// Applies the function f to each character of the
// string s, passing its index as the first argument
// and the character itself as the second. A new
// string is created (using malloc(3)) to store the
// results from the successive applications of f. 
