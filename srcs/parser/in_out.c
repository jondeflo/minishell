/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:05:15 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/04 15:11:46 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		n_input(t_cmd *cmd, int i)
{
	char	*tmp;

	tmp = cmd->infile;
	if (ft_strlen(cmd->args[i + 1]) > 0)
		cmd->infile = n_remove_file_quotes(&(*cmd), i + 1, 0);
	else
		cmd->infile = NULL;
	if (tmp)
		free(tmp);
	tmp = NULL;
}

void		n_output(t_cmd *cmd, int i)
{
	char	*tmp;

	tmp = cmd->outfile;
	if (ft_strlen(cmd->args[i + 1]) > 0)
		cmd->outfile = n_remove_file_quotes(&(*cmd), i + 1, 0);
	else
		cmd->outfile = NULL;
	if (tmp)
		free(tmp);
	tmp = NULL;
}

void		n_rewrite(t_cmd *cmd, int i)
{
	char *tmp;

	tmp = cmd->outfile;
	cmd->rewrite = 1;
	if (ft_strlen(cmd->args[i + 1]) > 0)
		cmd->outfile = n_remove_file_quotes(&(*cmd), i + 1, 0);
	else
		cmd->outfile = NULL;
	if (tmp)
		free(tmp);
	tmp = NULL;
}

char		*n_delete_file_quote(char **str, int i)
{
	char	*res;
	char	*tmp1;
	char	*tmp2;

	if (!(tmp1 = new_substr((*str), 0, i)))
		exit(-1);
	if (!(tmp2 = new_substr((*str), i + 1, ft_strlen(*str))))
		exit(-1);
	if (!(res = ft_strjoin(tmp1, tmp2)))
		exit(-1);
	free(tmp1);
	free(tmp2);
	free(*str);
	*str = NULL;
	return (res);
}

char		*n_remove_file_quotes(t_cmd *cmd, int k, size_t i)
{
	char	**ptr;

	ptr = &(cmd->args[k]);
	while (i < ft_strlen(cmd->args[k]))
	{
		if (cmd->args[k][i] && cmd->args[k][i] == '\'')
		{
			*ptr = n_delete_file_quote(&cmd->args[k], i);
			i = one_more_skip(cmd->args[k], '\'');
			*ptr = n_delete_file_quote(&cmd->args[k], i);
			i += 2;
		}
		else if (cmd->args[k][i] && cmd->args[k][i] == '"')
		{
			*ptr = n_delete_file_quote(&cmd->args[k], i);
			i = one_more_skip(cmd->args[k], '"');
			*ptr = n_delete_file_quote(&cmd->args[k], i);
			i += 2;
		}
		else
			i++;
	}
	return (ft_strdup(cmd->args[k]));
}
