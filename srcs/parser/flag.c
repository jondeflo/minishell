/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:48:22 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/04 15:50:18 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ret_fl(char *s, int i)
{
	if (s[i] == '>')
		return (1);
	if (s[i] == '<')
		return (3);
	return (0);
}

int		ret_fl_2(char *s, int i)
{
	if (s[i] && !s[i + 1])
		return (ret_fl(s, i));
	if ((s[i] && s[i + 1]) && (s[i] == '>' && s[i + 1] == '>'))
		return (2);
	if ((s[i] && s[i + 1]) && (s[i] == '>' && s[i + 1] == '<'))
		return (0);
	if ((s[i] && s[i + 1]) && (s[i] == '<' && s[i + 1] == '>'))
		return (0);
	return (-1);
}

int		extended_flag(char *s, int i)
{
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == '\'' || s[i] == '"')
			i = skip_char_2(s, i);
		if (s[i] && (s[i] != '>' && s[i] != '<') &&
		(s[i] != '\'' && s[i] != '"'))
			i++;
		else
		{
			if (ret_fl_2(s, i) >= 0)
				return (ret_fl_2(s, i));
			if (s[i] && s[i + 1])
			{
				if ((s[i] == '>' || s[i] == '<') &&
				(s[i + 1] != '>' || s[i + 1] != '<'))
				{
					if (s[i] == '>')
						return (1);
					if (s[i] == '<')
						return (3);
				}
			}
		}
	}
	return (0);
}

void	plus_cnt_three(int *cnt)
{
	cnt[3] += 2;
	cnt[2]++;
}

int		skip_char_2(char *str, int i)
{
	char	tmp;

	tmp = str[i];
	i++;
	while (str[i] && str[i] != tmp)
		i++;
	if (str[i])
		i++;
	return (i);
}
