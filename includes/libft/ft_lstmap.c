/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:45:11 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/20 19:26:18 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*new_node;
	void	*check;

	list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		check = f(lst->content);
		new_node = ft_lstnew(check);
		if (!new_node)
		{
			del(check);
			ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, new_node);
		lst = lst->next;
	}
	return (list);
}
