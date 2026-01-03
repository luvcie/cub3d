/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:09:56 by lucpardo          #+#    #+#             */
/*   Updated: 2025/06/03 10:57:50 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_string(char *str)
{
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_integer(int n)
{
	char	*str;
	int		i;

	str = ft_itoa(n);
	if (str == NULL)
	{
		return (0);
	}
	ft_putstr_fd(str, 1);
	i = ft_strlen(str);
	free(str);
	return (i);
}
