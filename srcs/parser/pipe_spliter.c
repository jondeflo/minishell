/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_spliter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:25:47 by ccaptain          #+#    #+#             */
/*   Updated: 2021/01/04 11:02:01 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**make_pipe_arr(char *str)
{
	int		i;
	int		cnt;
	char	**res;

	i = 0;
	cnt = 1;
	while (i < (int)ft_strlen(str))
	{
		i = symbol_skip(str, i, '|');
		if (str[i] == '\'' || str[i] == '"')
			i = pipe_quote_skip(str, i);
		if (i < (int)ft_strlen(str) && str[i] == '|')
		{
			cnt++;
		}
		i++;
	}
	if (!(res = malloc(sizeof(char *) * (cnt + 1))))
		exit(-1);
	res[cnt] = NULL;
	return (res);
}

int		symbol_skip(char *str, int i, char c)
{
	while (str[i] && (str[i] != '\'' && str[i] != '"' && str[i] != c))
		i++;
	return (i);
}

int		pipe_quote_skip(char *str, int i)
{
	char	tmp;

	tmp = str[i];
	i++;
	while (str[i] && (str[i] != tmp))
		i++;
	i++;
	return (i);
}

char	**split_by_pipes(char *str, int *cnt)
{
	char	**pipes;
	char	**ptr;

	ptr = &str;
	pipes = make_pipe_arr(str);
	while (cnt[0] < (int)ft_strlen(str))
	{
		cnt[1] = 0;
		cnt[0] = symbol_skip(str, cnt[0], '|');
		if (str[cnt[0]] == '\'' || str[cnt[0]] == '"')
			cnt[0] = pipe_quote_skip(str, cnt[0]);
		if (cnt[0] < (int)ft_strlen(str) && str[cnt[0]] == '|')
		{
			cnt[2] = cnt[0];
			pipes[cnt[3]] = new_substr(str, cnt[1], cnt[2]);
			cnt[3]++;
			*ptr = sub_str(&str, cnt[0] + 1, ft_strlen(str));
			cnt[0] = 0;
		}
	}
	pipes[cnt[3]] = ft_strdup(str);
	free(str);
	str = NULL;
	return (pipes);
}
