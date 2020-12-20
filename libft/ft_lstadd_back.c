/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 23:02:01 by ajeanett          #+#    #+#             */
/*   Updated: 2020/10/26 15:30:55 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elem;

	elem = *lst;
	if (lst == NULL || *lst == NULL)
		*lst = new;
	else
	{
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = new;
	}
}
