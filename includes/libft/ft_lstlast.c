/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:07:55 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/12 18:25:25 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
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

    t_list *last = ft_lstlast(lst1);

    if (last != NULL)
    {
        printf("%s\n", (char *)last->content);
    }
    else
    {
        printf("The list is empty.\n");
    }
    return 0;
}*/
