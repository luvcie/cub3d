/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:11:21 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/06 20:37:23 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*#include <stdio.h>
int	main(void)
{
	t_list	*head = ft_lstnew("1 3 3 7");
	head->next = ft_lstnew("7 1 5 7");
	printf("%d \n", ft_lstsize(head));
}*/
// i is not linked to lst, but lst and i 
// are incremented at the same time
// so i is the size of the linked list
// counts number of nodes in list
// lst: beginning of list
// return: len of list
