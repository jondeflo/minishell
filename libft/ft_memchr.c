/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 12:14:46 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/11 12:24:57 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ch;

	ch = (unsigned char *)s;
	while (n > 0)
	{
		if (*ch == (unsigned char)c)
			return ((unsigned char *)ch);
		ch++;
		n--;
	}
	return (0);
}
