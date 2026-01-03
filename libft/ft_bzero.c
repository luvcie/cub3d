/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:35:06 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/02 19:14:06 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void	*s, size_t	n)
{
	ft_memset(s, 0, n);
}
/*#include <stdio.h>
int	main(void)
{
	char	str[20];

	ft_bzero(str, 20);
	printf("%s \n", str);
	return (0);
}*/
