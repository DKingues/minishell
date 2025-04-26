/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:58:57 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/20 19:21:30 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

/*int main(void)
{
    t_list  *lst1 = ft_lstnew("e");
    t_list  *lst2 = ft_lstnew("l");
    t_list  *lst3 = ft_lstnew("l");
    t_list  *lst4 = ft_lstnew("o");

    lst1->next = lst2;
    lst2->next = lst3;
    lst3->next = lst4;
    lst4->next = NULL;

    ft_lstadd_front(&lst1, ft_lstnew("h"));

    t_list *current = lst1;
    while (current != NULL)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
    return 0;
}*/
