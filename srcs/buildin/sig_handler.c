/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:54:40 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/23 15:07:03 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_int_handler(int sgnl)
{
	if (sgnl == 2)
	{
		ft_putstr_fd("\b\b  ", 1);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("\e[1;33mshell>>\x1b[0m", 1);
		signal(SIGINT, sh_int_handler);
	}
	if (sgnl == 3)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		signal(SIGQUIT, sh_int_handler);
	}
}

void	cmd_int_handler(int sgnl)
{
	if (sgnl == 2)
		signal(SIGINT, cmd_int_handler);
	if (sgnl == 3)
		signal(SIGQUIT, cmd_int_handler);
}

void	sig_filler(t_ms *ms, int err)
{
	if (WIFSIGNALED(err))
	{
		if (WTERMSIG(err) == 2)
			ms->last_status = 130;
		if (WTERMSIG(err) == 3)
			ms->last_status = 131;
	}
	else if (WIFEXITED(err))
		ms->last_status = WEXITSTATUS(err);
}
