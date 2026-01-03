/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:49:02 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/02 00:29:08 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
/*#include <stdio.h>
int	main(void)
{
	printf("%d \n", ft_strlen("xXxh3ll0xXX"));
	printf("%d \n", ft_strlen("xXxw0RlDxXX"));
	printf("%d \n", ft_strlen("qwertyuiop"));
	return (0);
}*/
