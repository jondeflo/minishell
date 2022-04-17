/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:07:11 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/04 16:16:40 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		**get_group_arr(char *str)
{
	int		k;
	char	**res;

	k = count_groups(str);
	if (ft_strlen(str) == 0)
		return (NULL);
	if (!(res = (char**)malloc(sizeof(char *) * (k + 1))))
		exit(-1);
	res[k] = NULL;
	return (res);
}

int			count_groups(char const *str)
{
	int		i;
	int		q;
	int		res;
	char	tmp;

	i = 0;
	q = 1;
	res = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			q *= -1;
			tmp = str[i];
			i++;
			while (str[i] && str[i] != tmp)
				i++;
			q *= -1;
		}
		if (q > 0 && str[i] == ';')
			res++;
		if (str[i])
			i++;
	}
	return (res);
}

int			skip_char_1(char *str, int i)
{
	char	tmp;

	while (str[i] && (str[i] != ' ' && str[i] != '\'' && str[i] != '"'))
	{
		i++;
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '"')
			{
				tmp = str[i];
				i++;
				while (str[i] && str[i] != tmp)
					i++;
				if (str[i])
					i++;
			}
			if (str[i] != '\'' && str[i] != '"')
				break ;
		}
	}
	while (str[i] && (str[i] == ' ' && str[i] != '\'' && str[i] != '"'))
		i++;
	return (i);
}

char		**get_split_arr(char *str, int q1, int q2, int i)
{
	int		elem;
	int		t;

	elem = 0;
	while (i < (int)ft_strlen(str) && str[i])
	{
		while (str[i])
		{
			t = i;
			if (str[i] == '\'' || str[i] == '"')
				i = skip_char_2(str, i);
			if (str[i] && (str[i] != '\'' && str[i] != '"'))
				break ;
			if (!str[i] && t != i)
				elem++;
		}
		if (str[i] && q1 > 0 && q2 > 0)
		{
			i = skip_char_1(str, i);
			elem++;
		}
		else
			i++;
	}
	return (make_split_arr(elem));
}
