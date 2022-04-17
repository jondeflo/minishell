/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_eee.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:51:30 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/21 14:17:35 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			is_number(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int			ms_exit(t_ms *ms, char **args)
{
	ms->exit = 1;
	if (args[1] && args[2])
	{
		ms->last_status = -1;
		ft_putendl_fd("shell: exit: too many arguments", 2);
	}
	else if (args[1] && is_number(args[1]) == 1)
	{
		ms->last_status = -1;
		ft_putstr_fd("shell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (args[1] && is_number(args[1]) == 0)
		ms->last_status = ft_atoi(args[1]);
	else
		ms->last_status = 0;
	return (ms->last_status);
}

int			ms_env(t_ms *ms)
{
	t_list *tmp;

	tmp = ms->env;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
			ft_putendl_fd(tmp->content, 1);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (0);
}

int			ms_echo(char **args)
{
	int		newline;
	int		i;

	newline = 0;
	i = 1;
	if (args[1])
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			newline = 1;
			i++;
		}
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i] && args[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (newline == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}

void		free_exit(t_ms *ms)
{
	clear_list(&(ms->env));
	exit(ms->last_status);
}
