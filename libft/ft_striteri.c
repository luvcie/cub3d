/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:36:59 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/05 16:37:01 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*#include <stdio.h>
#include <ctype.h>
void	ft_f(unsigned int i, char *c)
{
	*c = toupper(*c);
}

int	main(void)
{
	char str[] = "ooooo";
	printf("%s \n", str);
	ft_striteri(str, ft_f);
    printf("%s\n", str);
    return (0);
}*/
