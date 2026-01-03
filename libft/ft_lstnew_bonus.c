/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:08:58 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/06 19:15:05 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (element == NULL)
		return (NULL);
	element -> next = NULL;
	element -> content = content;
	return (element);
}
/*#include <stdio.h>
int main(void)
{
	t_list *head = ft_lstnew("chair, table, floor, sofa, piano");
	head->next = ft_lstnew("person, bottle, furniture, pillow, music");
	
	printf("linked list:| %s | %s |\n",(char *)head->content, 
	(char *)head->next->content);
	return (0);
}*/
