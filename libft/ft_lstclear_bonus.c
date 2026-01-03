/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:32:11 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/07 13:32:49 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

// deletes and frees linked list
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next_node;

	if (lst == NULL || *lst == NULL || del == NULL)
	{
		return ;
	}
	current = *lst;
	while (current != NULL)
	{
		next_node = current->next;
		ft_lstdelone(current, del);
		current = next_node;
	}
	*lst = NULL;
}
/*)void ft_delete(void *content)
{
	if (content)
	{
		free(content);
	}
}
#include <stdio.h>
int	main(void)
{
	char *str0 = ft_strdup("aeiou"); //bc string 
	char *str1 = ft_strdup("iao");   //literals are not
	t_list *node0 = ft_lstnew(str0); //in heap or stack
	t_list *node1 = ft_lstnew(str1);

	node0->next = node1;
	printf("before clear: node0 content is \"%s\", node1 content is \"%s\"\n",
	(char *)node0->content, (char *)node1->content);
	t_list **head = &node0;
	ft_lstclear(head, ft_delete);
	printf("after clear: head is now %p\n", (void *)*head);
	return (0);
}*/
