/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:08:19 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/14 19:43:58 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
// j tracks number of words
// flag is a bool state flag to know if inside of word
static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	j;
	int	flag;	

	i = 0;
	j = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && flag == 0)
		{
			flag = 1;
			j++;
		}
		else if (str[i] == c)
		{
			flag = 0;
		}
		i++;
	}
	return (j);
}
// ignores delimiter char
// finds len of next word until delimiter
// allocates space for new word and copies extracted word to n

static char	*ft_extract_word(const char **str, char c)
{
	const char	*start;
	char		*word;
	int			len;

	while (**str == c)
	{
		(*str)++;
	}
	start = *str;
	while (**str && **str != c)
	{
		(*str)++;
	}
	len = *str - start;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static void	ft_free_arrays(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;

	if (s == 0)
		return (NULL);
	word_count = ft_count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (result == 0)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = ft_extract_word(&s, c);
		if (result[i] == 0)
		{
			ft_free_arrays(result, i);
			return (NULL);
		}
		i++;
	}
	result[word_count] = NULL;
	return (result);
}
/*#include <stdio.h>
int	main(void)
{
	char	**strstr;
	size_t	i;

	printf("%d \n", ft_count_words("hello universe I am floating in space",
			' '));
	strstr = ft_split(" hello univ erse I am floating in space", ' ');
	i = 0;
	while (i < 8)
	{
		printf("%s|", strstr[i]);
		i += 1;
	}
	return (0);
}*/
