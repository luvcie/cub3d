/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:21:41 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/02 00:27:03 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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
	printf("%d \n", ft_isprint('\t'));
	printf("%d \n", ft_isprint('t'));
	printf("%d \n", ft_isprint('6'));
	printf("%d \n", ft_isprint(999));
}*/
