/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:29:24 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/28 16:43:03 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			exec_prepare(t_exec *exec, char **env, t_ms *ms)
{
	int		ret;

	ret = 0;
	if (exec->i == 0 && exec->cmd->infile)
	{
		exec->fdin = open(exec->cmd->infile, O_RDONLY);
		if (exec->fdin < 0)
			ret = exec_open_in_err(&(*ms), &(*exec));
	}
	if (exec->i == 0 && !exec->cmd->infile)
		exec->fdin = dup(exec->tmpin);
	dup2(exec->fdin, 0);
	close(exec->fdin);
	if (exec->cmd->outfile)
		exec_out(&(*exec), &(*ms));
	else if (exec->i == exec->cmd_num - 1 && exec->cmd->outfile == NULL)
		exec->fdout = dup(exec->tmpout);
	else
		make_pipe(&(*exec));
	dup2(exec->fdout, 1);
	close(exec->fdout);
	exec_replace(&(*exec), &(*ms));
	if (!(exec->path = get_cmd_path(exec->cmd->args[0], env, 0)))
		ret = -1;
	return (ret);
}

void		exec_next(t_exec *exec)
{
	if (exec->path)
		free(exec->path);
	if (exec->cmd->infile)
		free(exec->cmd->infile);
	if (exec->cmd->outfile)
		free(exec->cmd->outfile);
	exec->i++;
	ft_free_arr(exec->cmd->args);
	exec->tmp = exec->tmp->next;
}

void		finish_exec(t_exec *exec, t_ms *ms, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	if (env)
		free(env);
	dup2(exec->tmpin, 0);
	dup2(exec->tmpout, 1);
	close(exec->tmpin);
	close(exec->tmpout);
	clear_list(&(ms->cmd_list));
}

void		init_exec(t_exec *exec, t_list *cmd_list)
{
	exec->tmpin = dup(0);
	exec->tmpout = dup(1);
	exec->cmd_num = ft_lstsize(cmd_list);
	exec->err = 0;
	exec->tmp = cmd_list;
	exec->i = 0;
	exec->path = NULL;
}

void		make_pipe(t_exec *exec)
{
	pipe(exec->fdpipe);
	exec->fdout = exec->fdpipe[1];
	exec->fdin = exec->fdpipe[0];
}
