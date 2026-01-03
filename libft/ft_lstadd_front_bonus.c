/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:16:46 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/06 20:04:09 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*#include <stdio.h>
int	main(void)
{
	t_list *list;
	list = ft_lstnew("list");
	ft_lstadd_front(&list, ft_lstnew("hackerlist"));
	printf("| %s | %s |\n", (char*)list->content, 
	(char*)list->next->content);
	return (0);
}*/
// Add the node 'new' at the beginning of the list
// lst: the address of a pointer to the first node of a list
// new: the address of a pointer to the node to be added
