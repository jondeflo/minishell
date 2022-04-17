/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 16:22:30 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/22 16:54:43 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (!new)
		return ;
	if (*lst)
	{
		tmp = *lst;
		while ((tmp)->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	else
		*lst = new;
}
