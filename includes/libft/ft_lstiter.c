/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:42:06 by dicosta-          #+#    #+#             */
/*   Updated: 2024/11/18 19:19:58 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;
	t_list	*aux;

	temp = lst;
	if (!f)
		return ;
	while (temp != NULL)
	{
		aux = temp;
		temp = temp->next;
		f(aux->content);
	}
}
