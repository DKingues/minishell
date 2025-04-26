/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:29:36 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/20 19:21:56 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*aux;

	if (lst == NULL || del == NULL)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		aux = temp;
		temp = temp->next;
		del(aux->content);
		free(aux);
	}
	*lst = NULL;
}
/*int main(void)
{
    t_list  *lst1 = ft_lstnew("1");
    t_list  *lst2 = ft_lstnew("2");
    t_list  *lst3 = ft_lstnew("3");
    t_list  *lst4 = ft_lstnew("4");

    write(1,lst1->content, 1);
    write(1, "\n", 1);
    write(1,lst2->content, 1);
    write(1, "\n", 1);
    write(1,lst3->content, 1);
    write(1, "\n", 1);
    write(1,lst4->content, 1);
    write(1, "\n", 1);

    ft_lstclear(&lst1, del);

    write(1,lst1->content, 1);
    write(1, "\n", 1);
    write(1,lst2->content, 1);
    write(1, "\n", 1);
    write(1,lst3->content, 1);
    write(1, "\n", 1);
    write(1,lst4->content, 1);
    write(1, "\n", 1);
}*/
