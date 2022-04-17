/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:18:19 by ccaptain          #+#    #+#             */
/*   Updated: 2020/12/23 15:08:39 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_jackdaw(char *arg)
{
	if (ft_strcmp(arg, ">") == 0)
		return (1);
	if (ft_strcmp(arg, "<") == 0)
		return (1);
	if (ft_strcmp(arg, ">>") == 0)
		return (1);
	if (ft_strcmp(arg, "<<") == 0)
		return (1);
	return (0);
}

int		ft_check_in(char *in, t_ms *ms)
{
	int			i;
	int			quote;
	int			dquote;

	i = -1;
	quote = 0;
	dquote = 0;
	if (ft_check_begin(in) == 1)
	{
		ms->last_status = 258;
		return (1);
	}
	while (in[++i] && in[i + 1] != '\0')
	{
		in[i] == '\'' ? quote++ : quote;
		in[i] == '"' ? dquote++ : dquote;
		if (ft_check(in, &i, quote, dquote) == 1)
		{
			ms->last_status = 258;
			return (1);
		}
		quote == 2 ? quote = 0 : quote;
		dquote == 2 ? dquote = 0 : dquote;
	}
	return (0);
}

int		begin(t_ms *ms)
{
	char		*in;
	char		*cut_in;

	in = NULL;
	ms->error = 0;
	ft_read_cmd(&in);
	if (ft_strlen(in) > 0)
	{
		cut_in = ft_strtrim(in, " ");
		free(in);
	}
	else
	{
		free(in);
		return (ms->error);
	}
	if (cut_in && ft_strlen(cut_in) > 0)
	{
		if (ft_check_in(cut_in, &(*ms)) == 0)
			parce_in(ms, ft_one_more_check_in(cut_in));
		else
			free(cut_in);
	}
	return (ms->error);
}
