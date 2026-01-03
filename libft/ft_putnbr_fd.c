/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:51:46 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 17:58:31 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	ssize_t	ret;

	if (n == -2147483648)
	{
		ret = write(fd, "-2147483648", 11);
		(void)ret;
		return ;
	}
	if (n < 0)
	{
		ret = write(fd, "-", 1);
		(void)ret;
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	ret = write(fd, &c, 1);
	(void)ret;
}
/*int	main(void)
{
	ft_putnbr_fd(1337, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-2147483648, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(111111, 0);
	write(1, "\n", 1);
	ft_putnbr_fd(8122036, 2);
	write(1, "\n", 1);
	return (0);
}*/
