/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:38:09 by ccaptain          #+#    #+#             */
/*   Updated: 2021/01/04 14:40:37 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_init_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->rewrite = 0;
	cmd->flag = 0;
	parce_out(&(*cmd), 0);
	while (cmd->args[i])
		i++;
	cmd->ac = i;
}

int			ft_free_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
	return (-1);
}

void		ft_decode_cmd(char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == 1)
			cmd[i] = ' ';
		if (cmd[i] == 2)
			cmd[i] = ';';
	}
}

char		*new_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	if (!(res = malloc(sizeof(char) * (len + 1))))
		exit(-1);
	while (i < len && s[start] != '\0')
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}
