/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:26:28 by ccaptain          #+#    #+#             */
/*   Updated: 2021/01/04 14:18:18 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_space(char *str, int *cnt)
{
	char	*tmp;

	if (!(tmp = malloc(sizeof(char) * ((ft_strlen(str) * 2) + 1))))
		exit(-1);
	while (cnt[2] < (int)ft_strlen(str))
	{
		check_q1_q2(str, cnt);
		if (cnt[0] > 0 && cnt[1] > 0)
		{
			if (check_special(str, cnt[2]) == 1)
			{
				tmp[cnt[3]] = str[cnt[2]];
				tmp[cnt[3] + 1] = ' ';
				plus_cnt_three(cnt);
			}
			else
				tmp[cnt[3]++] = str[cnt[2]++];
		}
		else
			tmp[cnt[3]++] = str[cnt[2]++];
	}
	tmp[cnt[3]] = '\0';
	free(str);
	str = NULL;
	return (tmp);
}

char	*remove_backslash(char *str, int *cnt)
{
	char	*tmp;

	tmp = ft_strdup(str);
	while (cnt[2] < (int)ft_strlen(str))
	{
		check_q1_q2(str, cnt);
		if (cnt[0] > 0 && cnt[1] > 0)
		{
			if (check_special_one(str, cnt) == 1)
				case_one(&(*str), &(*tmp), cnt);
			else if (check_special_two(str, cnt) == 1)
				case_two(&(*str), &(*tmp), cnt);
			else
				case_three(&(*str), &(*tmp), cnt);
		}
		else
			case_three(&(*str), &(*tmp), cnt);
	}
	tmp[cnt[3]] = '\0';
	free(str);
	str = NULL;
	return (tmp);
}

char	*remove_file_quotes(char *cmd, size_t i)
{
	char	**ptr;

	ptr = &cmd;
	while (i < ft_strlen(cmd))
	{
		if (cmd[i] && cmd[i] == '\'')
		{
			*ptr = delete_file_quote(&cmd, i);
			i = one_more_skip(cmd, '\'');
			*ptr = delete_file_quote(&cmd, i);
			i += 2;
		}
		else if (cmd[i] && cmd[i] == '"')
		{
			*ptr = delete_file_quote(&cmd, i);
			i = one_more_skip(cmd, '"');
			*ptr = delete_file_quote(&cmd, i);
			i += 2;
		}
		else
			i++;
	}
	return (return_file_name(cmd));
}

char	*remove_quotes(char *cmd, size_t i)
{
	char	**ptr;

	ptr = &cmd;
	while (i < ft_strlen(cmd))
	{
		if (cmd[i] && cmd[i] == '\'')
		{
			*ptr = delete_quote(&cmd, i);
			i = one_more_skip(cmd, '\'');
			*ptr = delete_quote(&cmd, i);
			i += 2;
		}
		else if (cmd[i] && cmd[i] == '"')
		{
			*ptr = delete_quote(&cmd, i);
			i = one_more_skip(cmd, '"');
			*ptr = delete_quote(&cmd, i);
			i += 2;
		}
		else
			i++;
	}
	return (cmd);
}

char	*remove_doublespace(char *str, int *c)
{
	char	*tmp;

	tmp = ft_strdup(str);
	while (c[2] < (int)ft_strlen(str))
	{
		check_q1_q2(str, c);
		if (c[0] > 0 && c[1] > 0)
		{
			if (str[c[2] + 1] && (str[c[2]] == ' ' && str[c[2] + 1] == ' '))
			{
				while (str[c[2] + 1] && str[c[2] + 1] == ' ')
					c[2]++;
				tmp[c[3]++] = str[c[2]++];
			}
			else
				tmp[c[3]++] = str[c[2]++];
		}
		else
			tmp[c[3]++] = str[c[2]++];
	}
	tmp[c[3]] = '\0';
	free(str);
	str = NULL;
	return (tmp);
}
