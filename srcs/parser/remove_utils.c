/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:17:40 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/04 14:18:51 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*delete_quote(char **str, int i)
{
	char	*res;
	char	*tmp1;
	char	*tmp2;

	tmp1 = new_substr((*str), 0, i);
	tmp2 = new_substr((*str), i + 1, ft_strlen(*str));
	res = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	free(*str);
	*str = NULL;
	return (res);
}

char	*delete_file_quote(char **str, int i)
{
	char	*res;
	char	*tmp1;
	char	*tmp2;

	tmp1 = new_substr((*str), 0, i);
	tmp2 = new_substr((*str), i + 1, ft_strlen(*str));
	res = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (res);
}

char	*return_file_name(char *cmd)
{
	char	*res;

	if (!(res = ft_strdup(cmd)))
		exit(-1);
	free(cmd);
	return (res);
}
