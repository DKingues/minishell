/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:25:30 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/20 19:20:07 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
	}
}

/*int main(void)
{
    t_list  *lst1;
    t_list  *lst2 = ft_lstnew("e");
    t_list  *lst3 = ft_lstnew("l");
    t_list  *lst4 = ft_lstnew("l");

 
    lst2->next = lst3;
    lst3->next = lst4;
    lst4->next = NULL;

    ft_lstadd_back(&lst1, ft_lstnew("o"));
    
    t_list *current = lst1;

    while (current != NULL)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
}*/
