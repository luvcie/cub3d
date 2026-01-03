/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:20:47 by lucpardo          #+#    #+#             */
/*   Updated: 2025/04/28 18:15:12 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*#include <stdio.h>
int	main(void)
{
	printf("%d \n", ft_isdigit('4'));
	printf("%d \n", ft_isdigit('a'));
	printf("%d \n", ft_isdigit('2'));
	printf("%d \n", ft_isdigit('&'));
	return (0);
}*/
