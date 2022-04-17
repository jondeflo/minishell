/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:57:27 by ccaptain          #+#    #+#             */
/*   Updated: 2021/01/04 16:19:07 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd		*get_args(char *cmd, t_ms *ms)
{
	int		i;
	t_cmd	*res;
	int		cnt[4];

	res = malloc(sizeof(t_cmd));
	init_split_args(cnt);
	i = 0;
	res->args = split_args(cmd, cnt, 0, NULL);
	res->ac = 0;
	while (res->args[res->ac] != NULL)
		res->ac++;
	i = 0;
	while (res->args[i])
		i++;
	if ((i == 2 && check_jackdaw(res->args[1])))
	{
		ms->error = 1;
		ms->last_status = 258;
	}
	ft_init_cmd(res);
	return (res);
}

t_cmd		**get_commands(char *com, t_ms *ms, int i)
{
	char	**pipes;
	t_cmd	**cmds;
	char	*tmp;
	int		cnt[4];

	init_cnt(cnt);
	pipes = split_by_pipes(com, cnt);
	while (pipes[i] != NULL)
		i++;
	if (!(cmds = malloc(sizeof(t_cmd) * (i + 1))))
		return (NULL);
	i = 0;
	while (pipes[i])
	{
		tmp = ft_strtrim(pipes[i], " ");
		free(pipes[i]);
		pipes[i] = NULL;
		cmds[i] = get_args(tmp, ms);
		i++;
	}
	free(pipes);
	cmds[i] = NULL;
	return (cmds);
}

void		free1_cmd_arr(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
			i++;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
}

void		parce_cmd(char *com, t_ms *ms)
{
	int		j;
	t_cmd	**cmds;

	cmds = get_commands(com, &(*ms), 0);
	j = 0;
	while (cmds[j])
	{
		fill_cmd_list(&(*ms), cmds[j]);
		if (cmds[j]->args)
			free1_cmd_arr((cmds[j]));
		if (cmds[j]->infile)
			free(cmds[j]->infile);
		if (cmds[j]->outfile)
			free(cmds[j]->outfile);
		free(cmds[j]);
		j++;
	}
	fill_queue(&(*ms));
	free(cmds);
}

int			parce_in(t_ms *ms, char *in)
{
	char	**groups;
	int		i;
	char	*tmp;
	int		cnt[4];

	i = 0;
	init_split_args(cnt);
	in = remove_backslash(in, cnt);
	init_split_args(cnt);
	in = remove_doublespace(in, cnt);
	init_split_args(cnt);
	init_cnt(cnt);
	groups = split_by_groups(in, cnt);
	while (groups && groups[i])
	{
		tmp = ft_strtrim(groups[i], " ");
		free(groups[i]);
		parce_cmd(tmp, &(*ms));
		i++;
	}
	if (groups)
		free(groups);
	return (ms->error);
}
