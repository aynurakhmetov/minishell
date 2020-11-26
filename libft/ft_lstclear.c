/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 23:01:50 by ajeanett          #+#    #+#             */
/*   Updated: 2020/10/26 15:30:49 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *elem;

	if (lst && del)
	{
		while (*lst != NULL)
		{
			elem = *lst;
			*lst = elem->next;
			del(elem->content);
			free(elem);
		}
	}
}
