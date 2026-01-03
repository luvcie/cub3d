/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:51:57 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/24 21:49:33 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

// %c Prints a single character.
// %s Prints a string (as defined by the common C convention).
// %p The void * pointer argument has to be printed in hexadecimal format.
// %d Prints a decimal (base 10) number.
// %i Prints an integer in base 10.
// %u Prints an unsigned decimal (base 10) number.
// %x Prints a number in hexadecimal (base 16) lowercase format.
// %X Prints a number in hexadecimal (base 16) uppercase format.
// %% Prints a percent sign.
static int	ft_echarpe(char specifier, va_list ap)
{
	if (specifier == 'c')
	{
		ft_putchar_fd((char)va_arg(ap, int), 1);
	}
	else
	{
		ft_putchar_fd('%', 1);
	}
	return (1);
}

int	ft_types(char format_specifier, va_list ap)
{
	if (format_specifier == 'c' || format_specifier == '%')
		return (ft_echarpe(format_specifier, ap));
	else if (format_specifier == 's')
		return (ft_string(va_arg(ap, char *)));
	else if (format_specifier == 'd' || format_specifier == 'i')
		return (ft_integer(va_arg(ap, int)));
	else if (format_specifier == 'u')
		return (ft_unsigned(va_arg(ap, unsigned int)));
	else if (format_specifier == 'x')
		return (ft_hexadecimal(va_arg(ap, unsigned int), 0));
	else if (format_specifier == 'X')
		return (ft_hexadecimal(va_arg(ap, unsigned int), 1));
	else if (format_specifier == 'p')
		return (ft_pointer(va_arg(ap, void *)));
	return (0);
}

// va_list holds list of variable args
// va_end finalizes argument pointer(ap)
int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		total_len;

	if (str == NULL)
		return (-1);
	total_len = 0;
	i = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == '\0')
				return (-1);
			total_len += ft_types(str[i], ap);
		}
		else
			total_len += write(1, &str[i], 1);
		i++;
	}
	va_end(ap);
	return (total_len);
}
