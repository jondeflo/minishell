/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 14:00:45 by jondeflo          #+#    #+#             */
/*   Updated: 2020/05/17 18:27:35 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *res;

	if (!(res = malloc(size * nmemb)))
		return (0);
	ft_bzero(res, size * nmemb);
	return (res);
}
