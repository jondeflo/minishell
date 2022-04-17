/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 11:38:19 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/23 16:41:14 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *res;

	res = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			res = s;
		s++;
	}
	if (c == '\0')
		return ((char*)s);
	return ((char*)res);
}
