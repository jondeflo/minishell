/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 12:37:42 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/11 13:14:04 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *ch1;
	unsigned char *ch2;

	ch1 = (unsigned char *)s1;
	ch2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*ch1 != *ch2)
			return ((unsigned char)(*ch1) - (unsigned char)(*ch2));
		else
		{
			ch1++;
			ch2++;
			n--;
		}
	}
	return (0);
}
