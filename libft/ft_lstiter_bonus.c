/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:57:05 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/13 22:38:39 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*node;

	if (lst == NULL || f == NULL)
		return ;
	node = lst;
	while (node != NULL)
	{
		f(node->content);
		node = node->next;
	}
}
/*
#include <stdio.h>
void	printf_weew(void *content)
{
	printf("%s\n", (char *)content);
}
int	main(void)
{
	t_list	*node0;
	t_list	*node1;
	t_list	*node2;

	node0 = ft_lstnew("weew");
	node1 = ft_lstnew("wlissa");
	node2 = ft_lstnew("giggling");

	node0->next = node1;
	node1->next = node2;
	ft_lstiter(node0, printf_weew);
}*/
// iterates through list 'lst' and applies function f
// to content of each node.
// lst: address of pointer to a node
// f: address of function to apply to each node's content
