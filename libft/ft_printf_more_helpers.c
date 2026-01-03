/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:26:14 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/30 19:43:29 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

// putcount recursively prints positive long integer
// and counts digits that have been printed
// used for unsigned helper functino
static int	ft_putucount(unsigned long nbr)
{
	int	i;

	i = 0;
	if (nbr >= 10)
	{
		i += ft_putucount(nbr / 10);
	}
	ft_putchar_fd((nbr % 10) + '0', 1);
	i++;
	return (i);
}

static int	ft_puthexcount(unsigned long nbr, const char *hex_type)
{
	int	i;

	i = 0;
	if (nbr >= 16)
	{
		i += ft_puthexcount(nbr / 16, hex_type);
	}
	ft_putchar_fd(hex_type[nbr % 16], 1);
	i++;
	return (i);
}

int	ft_unsigned(unsigned int u)
{
	if (u == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	return (ft_putucount((unsigned long)u));
}

int	ft_hexadecimal(unsigned int nbr, int isupper_flag)
{
	char	*hex_lower;
	char	*hex_upper;

	hex_lower = "0123456789abcdef";
	hex_upper = "0123456789ABCDEF";
	if (nbr == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	if (isupper_flag == 1)
	{
		return (ft_puthexcount((unsigned long)nbr, hex_upper));
	}
	else
	{
		return (ft_puthexcount((unsigned long)nbr, hex_lower));
	}
}

int	ft_pointer(void *ptr)
{
	int				i;
	unsigned long	j;

	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	else
	{
		i = 0;
		ft_putstr_fd("0x", 1);
		i += 2;
		j = (unsigned long)ptr;
		i += ft_puthexcount(j, "0123456789abcdef");
	}
	return (i);
}
