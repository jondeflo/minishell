/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:40:56 by ccaptain          #+#    #+#             */
/*   Updated: 2021/01/04 15:48:42 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		n_remove_two_args(t_cmd *cmd, int i, int k, int j)
{
	char	**res;

	while (cmd->args[k])
		k++;
	if (!(res = (char **)malloc(sizeof(char *) * (k - 1))))
		exit(-1);
	while (j < i)
	{
		res[j] = ft_strdup(cmd->args[j]);
		free(cmd->args[j]);
		j++;
	}
	free(cmd->args[i]);
	free(cmd->args[i + 1]);
	i += 2;
	while (j < (k - 2))
	{
		res[j] = ft_strdup(cmd->args[i]);
		free(cmd->args[i]);
		j++;
		i++;
	}
	res[j] = NULL;
	free(cmd->args);
	cmd->args = res;
}

void		n_remove_one_arg(t_cmd *cmd, int i, int k, int j)
{
	char	**res;

	while (cmd->args[k])
		k++;
	if (!(res = (char **)malloc(sizeof(char *) * (k))))
		exit(-1);
	while (j < i)
	{
		res[j] = ft_strdup(cmd->args[j]);
		free(cmd->args[j]);
		j++;
	}
	free(cmd->args[i]);
	i++;
	while (j < (k - 1))
	{
		res[j] = ft_strdup(cmd->args[i]);
		free(cmd->args[i]);
		j++;
		i++;
	}
	res[j] = NULL;
	free(cmd->args);
	cmd->args = res;
}

void		parce_out(t_cmd *cmd, int i)
{
	while (i < cmd->ac)
	{
		cmd->flag = extended_flag(cmd->args[i], 0);
		if ((cmd->flag == 1 || cmd->flag == 3) &&
		(ft_strlen(cmd->args[i]) == 1) && (cmd->args[i + 1]))
			make_in_out(&(*cmd), i);
		else if (cmd->flag == 2 && ft_strlen(cmd->args[i]) == 2 &&
		cmd->args[i + 1])
			make_rewrite(&(*cmd), i);
		else if (cmd->flag > 0)
			make_redir(&(*cmd), i);
		else
			i++;
	}
	i = 0;
	while (cmd->args[i])
		i++;
	cmd->ac = i;
}
