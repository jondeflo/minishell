/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 14:14:40 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/23 16:24:15 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		print_nbr(int n, int fd)
{
	if (n >= 10)
		print_nbr(n / 10, fd);
	if (n < 0)
	{
		if (n / 10 != 0)
			print_nbr((-1 * (n / 10)), fd);
		print_nbr((-1 * (n % 10)), fd);
	}
	else
		ft_putchar_fd((n % 10 + 48), fd);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	print_nbr(n, fd);
}
