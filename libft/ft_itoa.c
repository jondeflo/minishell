/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 17:21:29 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/23 15:46:21 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(int n)
{
	int		res;

	res = 0;
	if (n < 0)
		res++;
	while (n)
	{
		n = n / 10;
		res++;
	}
	return (res);
}

static char	*make_zero(void)
{
	char	*res;

	if (!(res = malloc(sizeof(char) * 2)))
		return (0);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		neg;

	neg = (n < 0 ? 1 : 0);
	len = count_char(n);
	if (n == 0 || n == -0)
		return (make_zero());
	if (!(res = malloc(sizeof(char) * len + 1)))
		return (0);
	if (n < 0)
		res[0] = '-';
	res[len] = '\0';
	len--;
	while (len >= neg)
	{
		res[len] = (n < 0 ? (-1 * (n % 10) + 48) : ((n % 10) + 48));
		n = n / 10;
		len--;
	}
	return (res);
}
