/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:44:04 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/14 01:06:18 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;
	void	*new_content;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			if (del != NULL)
				del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*#include <stdio.h>
void	*ft_up(void *s)
{
	char *new;
	int	i;

	new = ft_strdup(s);
	i = 0;
	while (new[i])
	{
		new[i] = ft_toupper(new[i]);
		i++;
	}
	return (new);
}

void	ft_delete(void *p)
{
	free(p);
}

int	main(void)
{
	t_list	*node0;
	t_list	*node1;
	t_list	*node2;
	t_list	*now;
	t_list	*mapped;

	node0 = ft_lstnew(ft_strdup("aeiou"));
	node1 = ft_lstnew(ft_strdup("qwerty"));
	node2 = ft_lstnew(ft_strdup("uiop"));
	ft_lstadd_back(&node0, node1);
	ft_lstadd_back(&node0, node2);
	mapped = ft_lstmap(node0, ft_up, ft_delete);
	now = mapped;
	while (now != NULL)
	{
		printf("%s \n", (char *)now->content);
		now = now->next;
	}
	ft_lstclear(&mapped, ft_delete);
	ft_lstclear(&node0, ft_delete);
	return (0);
}*/
// iterates through list 'lst', applies function 'f'
// to each node's content. And creates a new list resulting
// of the successive applications of function 'f'. 'del' function
// is used to delete the content of a node if needed.
// 
// lst: address of pointer to node
// f: address of function applied to each node's content
// del: address of the function used to delete a node's content
// if needed.
