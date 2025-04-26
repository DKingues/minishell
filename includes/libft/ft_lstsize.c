/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:05:12 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/20 19:27:51 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/*int main(void)
{
    t_list  *lst1 = ft_lstnew("1");
    t_list  *lst2 = ft_lstnew("2");
    t_list  *lst3 = ft_lstnew("3");
    t_list  *lst4 = ft_lstnew("4");

    lst1->next = lst2;
    lst2->next = lst3;
    lst3->next = lst4;
    lst4->next = NULL;

    printf("%d\n", ft_lstsize(lst1));
}*/
