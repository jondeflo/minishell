/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:59:18 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/04 17:50:55 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ms_export(t_ms *ms, char **args)
{
	int	i;
	int ret;

	i = 1;
	ret = 0;
	if (!args[1])
		return (print_empty_export(&(*ms)));
	else
	{
		while (args[i])
		{
			if (check_env_val(args[i]) == -1)
			{
				ft_putendl_fd("not a valid export argument", 2);
				ret = 1;
			}
			else
				add_env(&(*ms), args[i]);
			i++;
		}
		ms->last_status = ret;
		return (ret);
	}
	ms->last_status = ret;
	return (ret);
}

int		print_empty_export(t_ms *ms)
{
	t_list	*tmp;

	tmp = ms->env;
	ft_list_sort(&tmp);
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_ends_with(tmp->content, '='))
		{
			ft_putstr_fd((char *)tmp->content, 1);
			ft_putendl_fd("\"\"", 1);
		}
		else
			ft_putendl_fd(tmp->content, 1);
		tmp = tmp->next;
	}
	tmp = NULL;
	return (0);
}

void	ft_list_sort(t_list **begin_list)
{
	t_list	*i;
	t_list	*j;
	void	*temp_data;

	i = *begin_list;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->content, j->content) > 0)
			{
				temp_data = i->content;
				i->content = j->content;
				j->content = temp_data;
			}
			j = j->next;
		}
		i = i->next;
	}
}

int		add_env(t_ms *ms, char *str)
{
	t_list	*tmp;
	char	*tmpname;
	char	*strname;

	tmp = ms->env;
	strname = env_name(str);
	while (tmp)
	{
		tmpname = env_name(tmp->content);
		if (ft_strcmp(tmpname, strname) == 0)
		{
			free(tmp->content);
			if (!(tmp->content = ft_strdup(str)))
				exit(-1);
			free(tmpname);
			free(strname);
			return (0);
		}
		tmp = tmp->next;
		free(tmpname);
	}
	ft_lstadd_back(&ms->env, ft_lstnew(ft_strdup(str)));
	free(strname);
	return (0);
}

int		print_err_msg(char *str)
{
	ft_putstr_fd("shell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier\n", 2);
	return (-1);
}
