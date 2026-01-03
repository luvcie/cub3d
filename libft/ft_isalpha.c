/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:06:51 by lucpardo          #+#    #+#             */
/*   Updated: 2025/04/28 18:56:49 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
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
	printf("%d \n", ft_isalpha('5'));
	printf("%d \n", ft_isalpha('a'));
	return (0);
}*/
