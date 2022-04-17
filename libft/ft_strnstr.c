/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 18:37:56 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/25 14:07:24 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (little[j] == '\0' || big == little)
		return (char *)(big);
	while (big[i] != '\0' && i < len)
	{
		while (big[i] == little[j] && i < len && little[j] != '\0')
		{
			i++;
			j++;
		}
		if (little[j] == '\0')
			return (char *)(big + i - j);
		i = i - j + 1;
		j = 0;
	}
	return (0);
}
