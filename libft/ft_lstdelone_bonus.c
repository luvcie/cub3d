/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:32:26 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/07 12:10:58 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstdelone(t_list	*lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
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
	char *str = ft_strdup("aeiou");
	t_list *node = ft_lstnew(str);
	printf("%s\n", (char *)node->content);
	ft_lstdelone(node, ft_delete);
	printf("%s\n", (char *)node->content);
	return (0);
}*/
// takes node as param and frees its content
// using function 'del', free node but NOT
// the next node.
// lst: node to free
// del: address of function used to delete content
