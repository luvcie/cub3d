/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:10:03 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/08 18:17:36 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t	size)
{
	char	*ptr;
	size_t	total_bytes;

	if (nmemb == 0 || size == 0)
		total_bytes = 0;
	if (size != 0 && nmemb > (INT_MAX / size))
		return (NULL);
	total_bytes = nmemb * size;
	ptr = malloc(total_bytes);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_bytes);
	return (ptr);
}
/*#include <stdio.h>
int	main(void)
{
	void	*ptr = ft_calloc(30, 100);
	printf("%p \n", ptr);
	printf("%d \n", ((char *)ptr)[0]);
	return (0);
}*/
// allocates memory for an array of nmemb elements of
// size bytes each and returns a pointer to the allocated
// memory. Memory is set to zero. If nmemb or size is 0
// calloc() returns either NULL or unique pointer value
// that can be later passed to free().
