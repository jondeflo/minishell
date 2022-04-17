/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 11:58:05 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/25 09:52:40 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_ch(char ch, const char *set)
{
	unsigned int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (ch == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	begin;
	unsigned int	end;
	char			*res;
	unsigned int	len;

	if (!s1)
		return (0);
	if (!set)
		return (char *)(s1);
	begin = 0;
	end = 0;
	while (check_ch(s1[begin], set))
		begin++;
	while (check_ch(s1[ft_strlen(s1) - 1 - end], set) && begin < ft_strlen(s1))
		end++;
	len = ft_strlen(s1) - begin - end;
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (0);
	ft_strlcpy(res, s1 + begin, (ft_strlen(s1) - begin - end + 1));
	return (res);
}
