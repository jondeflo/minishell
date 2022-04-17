/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:12:45 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/21 14:12:47 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		exec_cmd_end(t_exec *exec, t_ms *ms, char **env)
{
	finish_exec(&(*exec), &(*ms), env);
	return (ms->last_status);
}

int		fork_error(t_ms *ms)
{
	ms->last_status = -1;
	return (-1);
}

void	make_fork(t_ms *ms)
{
	ms->pid = fork();
	signal(SIGINT, cmd_int_handler);
	signal(SIGQUIT, cmd_int_handler);
}

void	pre_exec_buildin(t_ms *ms, t_exec *exec)
{
	exec->err = exec_buildin(&(*ms), exec->cmd->args);
	exit(exec->err);
}

void	pre_exec_alien(t_exec *exec, char **env)
{
	execve(exec->path, exec->cmd->args, env);
	exec->err = get_error_msg(exec->path, 0);
	exit(exec->err);
}
