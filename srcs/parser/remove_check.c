/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:32:35 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/21 11:35:42 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_q1_q2(char *str, int *cnt)
{
	if (str[cnt[2]] == '"')
		cnt[0] *= -1;
	if (str[cnt[2]] == '\'')
		cnt[1] *= -1;
}

int		check_special(char *str, int i)
{
	if (str[i] && str[i + 1] && (str[i] == '>' && str[i + 1] != '>'))
		return (1);
	return (0);
}

int		check_special_one(char *str, int *cnt)
{
	if (str[cnt[2] + 1] && (str[cnt[2]] == '\\'
	&& str[cnt[2] + 1] == '\\'))
		return (1);
	return (0);
}

int		check_special_two(char *str, int *cnt)
{
	if (str[cnt[2] + 1] && (str[cnt[2]] == '\\'
	&& str[cnt[2] + 1] != '\\'))
		return (1);
	return (0);
}

size_t	one_more_skip(char *str, char ch)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != ch)
		i++;
	return (i);
}
