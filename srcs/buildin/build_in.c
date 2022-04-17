/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:36:45 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/27 11:22:53 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			is_buildin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int			exec_buildin(t_ms *ms, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ms_echo(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ms_pwd());
	if (ft_strcmp(args[0], "env") == 0)
		return (ms_env(&(*ms)));
	if (ft_strcmp(args[0], "export") == 0)
		return (ms_export(&(*ms), args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ms_unset(&(*ms), args, 1));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ms_cd(&(*ms), args));
	if (ft_strcmp(args[0], "exit") == 0)
		return (ms_exit(&(*ms), args));
	return (-1);
}
