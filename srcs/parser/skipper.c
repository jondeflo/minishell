/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skipper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:27:24 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/20 15:05:08 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		skip_quote_s(char *str, int i)
{
	while (str[i] && (str[i] != '\'' && str[i] != '$'))
		i++;
	return (i);
}

int		skip_till_next(char *str, int i)
{
	i++;
	while (str[i] && (str[i] != '\''))
		i++;
	i++;
	return (i);
}

void	skip_space_quote(char *str, int *count)
{
	count[1] = count[0];
	while (str[count[0]] && str[count[0]] != ' ' && str[count[0]] != '"')
		count[0]++;
}

int		skip_symbols(char *str, int i)
{
	while (str[i] && (str[i] != '\'' && str[i] != '"' && str[i] != '~'))
		i++;
	return (i);
}

void	reset_count(int *count)
{
	count[0] = 0;
	count[1] = 0;
}
