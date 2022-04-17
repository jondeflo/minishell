/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ends_with.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:13:09 by jondeflo          #+#    #+#             */
/*   Updated: 2020/11/01 14:18:34 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ends_with(char *str, char ch)
{
	if (!str || ch == 0)
		return (0);
	if (str[ft_strlen(str) - 1] == ch)
		return (1);
	return (0);
}
