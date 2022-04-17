/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:04:00 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/03 12:01:38 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_env(t_ms *ms, char **env, int ac, char **av)
{
	t_list		*my_env;
	t_list		*tmp;
	int			i;

	(void)ac;
	(void)av;
	my_env = NULL;
	i = 0;
	while (env[i])
	{
		if (!(tmp = ft_lstnew(ft_strdup(env[i++]))))
			exit(-1);
		ft_lstadd_back(&(my_env), tmp);
	}
	ms->env = my_env;
	ms->cmd_list = NULL;
	ms->queue = NULL;
	ms->last_status = 0;
	ms->cmd_list = NULL;
	ms->exit = -1;
}

int		the_main_fn(t_ms *ms, t_exec *exec, char **env)
{
	make_fork(&(*ms));
	if (ms->pid == 0 && is_buildin(exec->cmd->args[0]) == 1)
		pre_exec_buildin(&(*ms), &(*exec));
	if (ms->pid == 0 && is_buildin(exec->cmd->args[0]) != 1
	&& ft_strchr(exec->path, '/'))
		pre_exec_alien(&(*exec), env);
	if (ms->pid < 0 || waitpid(ms->pid, &(*exec).err, 0) == -1)
		return (fork_error((&(*ms))));
	return (0);
}

int		exec_cmd(t_ms *ms, t_list *cmd_list, char **env)
{
	t_exec	exec;

	init_exec(&exec, cmd_list);
	while (exec.i < exec.cmd_num)
	{
		exec.cmd = exec.tmp->content;
		if (exec_prepare(&exec, env, &(*ms)) != -1)
		{
			if (is_buildin(exec.cmd->args[0]) == 1 && ft_lstsize(cmd_list) == 1)
				exec.err = exec_buildin(&(*ms), exec.cmd->args);
			else if (check_stat(exec.path) == 1)
				the_main_fn(&(*ms), &exec, env);
			else
			{
				exec.err = get_error_msg(exec.path, 0);
				ms->last_status = exec.err;
			}
			sig_filler(&(*ms), exec.err);
		}
		exec_next(&exec);
	}
	return (exec_cmd_end(&exec, &(*ms), env));
}
