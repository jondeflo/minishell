/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:07:41 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/04 15:10:49 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		make_in_out(t_cmd *cmd, int i)
{
	if (cmd->flag == 1 && (cmd->args[i + 1]))
		n_output(&(*cmd), i);
	else if (cmd->flag == 3 && (cmd->args[i + 1]))
		n_input(&(*cmd), i);
	n_remove_two_args(&(*cmd), i, 0, 0);
	cmd->ac -= 2;
}

void		make_rewrite(t_cmd *cmd, int i)
{
	n_rewrite(&(*cmd), i);
	n_remove_two_args(&(*cmd), i, 0, 0);
	cmd->ac -= 2;
}

void		make_redir(t_cmd *cmd, int i)
{
	n_remove_redirect(&(*cmd), i);
	if (cmd->args[i])
	{
		if (cmd->flag == 1)
			n_output(&(*cmd), i - 1);
		else if (cmd->flag == 2)
			n_rewrite(&(*cmd), i - 1);
		else if (cmd->flag == 3)
			n_input(&(*cmd), i - 1);
	}
	n_remove_one_arg(&(*cmd), i, 0, 0);
	cmd->ac--;
}

void		n_remove_redirect(t_cmd *cmd, int k)
{
	char	*res;

	res = n_remove_file_quotes(&(*cmd), k, ft_strlen(cmd->args[k]));
	free(res);
	if (ft_strlen(cmd->args[k]) >= 2)
	{
		if (cmd->args[k][0] == '>' && cmd->args[k][1] == '>')
			res = new_substr(cmd->args[k], 2, ft_strlen(cmd->args[k]));
		if (cmd->args[k][0] == '>' && cmd->args[k][1] != '>')
			res = new_substr(cmd->args[k], 1, ft_strlen(cmd->args[k]));
		if (cmd->args[k][0] == '<')
			res = new_substr(cmd->args[k], 1, ft_strlen(cmd->args[k]));
		free(cmd->args[k]);
		if (ft_strlen(res) > 0)
			cmd->args[k] = res;
		else
		{
			free(res);
			cmd->args[k] = ft_strdup("");
		}
	}
}

void		free_cmd_arr(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
			i++;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
}
