/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:08:49 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/07 02:11:44 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

// adds node to end of linked list
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (lst == NULL || new == NULL)
	{
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
/*#include <stdio.h>
int	main(void)
{
	t_list *list;
	list = ft_lstnew("head");
	ft_lstadd_back(&list, ft_lstnew("test"));
	printf("| %s | %s |\n", (char*)list->content, 
	(char*)list->next->content);
	return (0);
}*/
