/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:47:27 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/07 01:03:28 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
	{
		return (NULL);
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
/*#include <stdio.h>
int	main(void)
{
	t_list	*head;
	head = ft_lstnew("e, w, i, w, a");
	head->next = ft_lstnew("w, e, e, w");
	head->next->next = ft_lstnew("L, I, S, T, S");
	printf("head: %p \n", head);
	printf("middle: %p \n", head->next);
	printf("last: %p \n", head->next->next);
	printf("last using function on head: %p \n", 
	ft_lstlast(head));
	return (0);
}*/
// returns last node of the list
// lst: beginning of list
