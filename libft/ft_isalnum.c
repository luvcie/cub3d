/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:29:12 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/01 19:52:29 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/*#include <stdio.h>
int		main(void)
{
	printf("%d \n", ft_isalnum('3'));
	printf("%d \n", ft_isalnum('a'));
	printf("%d \n", ft_isalnum('&'));
	printf("%d \n", ft_isalnum('%'));
	return (0);
}*/
