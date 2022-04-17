/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:17:09 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/28 16:42:58 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		exec_open_in_err(t_ms *ms, t_exec *exec)
{
	ft_putstr_fd("shell: ", 2);
	ft_putstr_fd(exec->cmd->args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(exec->cmd->infile, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	ms->last_status = 15;
	return (-1);
}

int		exec_open_out_err(t_ms *ms, t_exec *exec)
{
	ft_putstr_fd("shell: ", 2);
	ft_putstr_fd(exec->cmd->outfile, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	ms->last_status = 1;
	return (-1);
}

int		exec_out(t_exec *exec, t_ms *ms)
{
	int ret;

	ret = 0;
	if (exec->cmd->rewrite == 0)
		exec->fdout = open(exec->cmd->outfile, O_CREAT | O_RDWR |
			O_TRUNC, S_IRWXU);
	else
		exec->fdout = open(exec->cmd->outfile, O_CREAT |
			O_RDWR | O_APPEND, S_IRWXU);
	if (exec->fdout < 0)
		ret = exec_open_out_err(&(*ms), &(*exec));
	return (ret);
}

void	exec_replace(t_exec *exec, t_ms *ms)
{
	int i;

	i = 0;
	while (exec->cmd->args[i])
	{
		if (!(exec->cmd->args[i] = ft_replace(exec->cmd->args[i], &(*ms))))
			exit(-1);
		if (!(exec->cmd->args[i] = remove_quotes(exec->cmd->args[i], 0)))
			exit(-1);
		i++;
	}
}

int		check_stat(char *path)
{
	struct stat	*buf;
	int			res;
	int			st;

	res = 0;
	if (!(buf = malloc(sizeof(struct stat))))
		exit(-1);
	st = stat(path, buf);
	if (st == 0 && (buf->st_mode & S_IXUSR) && (S_ISDIR(buf->st_mode) == 0))
		res = 1;
	free(buf);
	return (res);
}
