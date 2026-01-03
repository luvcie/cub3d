/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:51:46 by lucpardo          #+#    #+#             */
/*   Updated: 2025/04/28 19:32:44 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d \n", ft_isascii(0));
	printf("%d \n", ft_isascii(9));
	printf("%d \n", ft_isascii(127));
	printf("%d \n", ft_isascii(128));
	printf("%d \n", ft_isascii(255));
	printf("%d \n", ft_isascii(500));
	printf("%d \n", ft_isascii('A'));
	printf("%d \n", ft_isascii('$'));
	printf("%d \n", ft_isascii('c'));
	printf("%d \n", ft_isascii('1'));
	printf("%d \n", ft_isascii('I'));
	printf("%d \n", ft_isascii('\t'));
	printf("%d \n", ft_isascii('\a'));
	printf("%d \n", ft_isascii('\b'));
	printf("%d \n", ft_isascii('\0'));
	return (0);
}*/
