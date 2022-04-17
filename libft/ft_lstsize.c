/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 15:54:23 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/22 16:07:34 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		res;
	t_list	*tmp;

	res = 1;
	tmp = lst;
	if (tmp != 0)
		while (tmp->next != 0)
		{
			tmp = tmp->next;
			res++;
		}
	else
		return (0);
	return (res);
}
