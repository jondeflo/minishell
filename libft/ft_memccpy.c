/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 15:07:21 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/23 19:20:41 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n > 0)
	{
		*((unsigned char *)dest) = *((unsigned char *)src);
		if ((unsigned char)c == *((unsigned char *)dest))
			return ((unsigned char *)dest + 1);
		dest = (unsigned char *)dest + 1;
		src = (unsigned char *)src + 1;
		n--;
	}
	return (0);
}
