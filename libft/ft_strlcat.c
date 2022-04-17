/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 13:48:51 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/23 15:14:19 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t len;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	len = i;
	while (i + 1 < size && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (len < size)
		dst[i] = '\0';
	return (ft_strlen(src) + len);
}
