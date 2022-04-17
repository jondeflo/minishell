/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:42:23 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/04 11:57:43 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		fill_queue(t_ms *ms)
{
	ft_lstadd_back(&ms->queue, ft_lstnew(ms->cmd_list));
	ms->cmd_list = NULL;
}

char		**copy_arr(char **av)
{
	int		i;
	char	**res;

	i = 0;
	while (av[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (av[i])
	{
		res[i] = ft_strdup(av[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void		fill_cmd_list(t_ms *ms, t_cmd *src)
{
	t_cmd	*cmd;

	if ((src) && (src->args[0]) && ms->error != 1)
	{
		if (!(cmd = malloc(sizeof(t_cmd))))
			exit(-1);
		cmd->args = copy_arr(src->args);
		cmd->infile = src->infile == NULL ? NULL : ft_strdup(src->infile);
		cmd->outfile = src->outfile == NULL ? NULL : ft_strdup(src->outfile);
		cmd->rewrite = src->rewrite;
		ft_lstadd_back(&ms->cmd_list, ft_lstnew(cmd));
	}
	else
		ft_putendl_fd("syntax error", 1);
}

void		clear_list(t_list **begin_list)
{
	if (*begin_list && (*begin_list)->next)
		clear_list(&(*begin_list)->next);
	if ((*begin_list)->content)
	{
		free((*begin_list)->content);
		(*begin_list)->content = NULL;
	}
	if ((*begin_list))
		free(*begin_list);
	*begin_list = NULL;
}

char		**lst_to_env(t_ms *ms)
{
	char	**res;
	int		i;
	t_list	*tmp;

	tmp = ms->env;
	i = 0;
	if (!(res = (char**)malloc(sizeof(char *) *
	(ft_lstsize(ms->env) + 1))))
		exit(-1);
	while (tmp->next)
	{
		if (!(res[i] = ft_strdup(tmp->content)))
			exit(-1);
		else
			tmp = tmp->next;
		i++;
	}
	if (!(res[i] = ft_strdup(tmp->content)))
		exit(-1);
	i++;
	res[i] = NULL;
	return (res);
}
