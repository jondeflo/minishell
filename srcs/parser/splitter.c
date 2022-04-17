/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:03:09 by ccaptain          #+#    #+#             */
/*   Updated: 2021/01/04 16:35:49 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fill_split(char *str, int i)
{
	char	*res;

	if (str[i] == '\0')
		res = new_substr(str, 0, i);
	else
		res = new_substr(str, 0, i - 1);
	return (res);
}

char	*fill_split_1(char *str, int *cnt)
{
	char	*res;

	cnt[2] = skip_char_1(str, cnt[2]);
	if (str[cnt[2]] == '\0')
		res = new_substr(str, 0, cnt[2]);
	else
		res = new_substr(str, 0, cnt[2] - 1);
	return (res);
}

char	**split_args(char *str, int *cnt, int t, char **split)
{
	split = get_split_arr(str, cnt[0], cnt[1], 0);
	while (cnt[2] < (int)ft_strlen(str) && str[cnt[2]])
	{
		t = cnt[2];
		while (str[cnt[2]])
		{
			if (str[cnt[2]] == '\'' || str[cnt[2]] == '"')
				norme_pleasurer(str, cnt);
			if (str[cnt[2]] && (str[cnt[2]] != '\'' && str[cnt[2]] != '"'))
				break ;
			if (!str[cnt[2]] && t != cnt[2])
				split[cnt[3]++] = fill_split(str, cnt[2]);
		}
		if (str[cnt[2]] && (cnt[0] > 0 && cnt[1] > 0))
		{
			split[cnt[3]++] = fill_split_1(str, cnt);
			if (cnt[2] >= (int)ft_strlen(str))
				break ;
			str = sub_str_1(&str, cnt[2], ft_strlen(str), cnt);
		}
		else
			cnt[2]++;
	}
	free(str);
	return (split);
}

char	*sub_str(char **s, int start, int len)
{
	char	*res;
	int		i;

	i = 0;
	if (start > len)
		len = 0;
	if (!(res = malloc(sizeof(char) * (len + 1))))
		exit(-1);
	while (i < len && (*s)[start] != '\0')
	{
		res[i] = (*s)[start];
		i++;
		start++;
	}
	res[i] = '\0';
	free(*s);
	*s = NULL;
	return (res);
}

char	**split_by_groups(char *str, int *cnt)
{
	char	**res;
	char	**ptr;

	ptr = &str;
	res = get_group_arr(str);
	while (cnt[0] < (int)ft_strlen(str))
	{
		cnt[1] = 0;
		cnt[0] = symbol_skip(str, cnt[0], ';');
		if (str[cnt[0]] == '\'' || str[cnt[0]] == '"')
			cnt[0] = pipe_quote_skip(str, cnt[0]);
		if (cnt[0] < (int)ft_strlen(str) && str[cnt[0]] == ';')
		{
			cnt[2] = cnt[0];
			res[cnt[3]++] = new_substr(str, cnt[1], cnt[2]);
			*ptr = sub_str(&str, cnt[0] + 1, ft_strlen(str));
			cnt[0] = 0;
		}
	}
	res[cnt[3]] = ft_strdup(str);
	free(str);
	str = NULL;
	return (res);
}
