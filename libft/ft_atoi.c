/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 12:59:52 by jondeflo          #+#    #+#             */
/*   Updated: 2020/09/30 14:10:25 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int					cnt;
	int					sign;
	unsigned long long	res;

	cnt = 0;
	res = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == 45)
		sign = -1;
	if (*nptr == 45 || *nptr == 43)
		nptr++;
	while (*nptr >= 48 && *nptr <= 57)
	{
		res = *nptr - 48 + (res * 10);
		nptr++;
		cnt++;
	}
	if (cnt > 19)
		return (sign == -1 ? 0 : -1);
	return (int)(res * sign);
}
