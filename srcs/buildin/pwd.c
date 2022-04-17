/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:44:15 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/21 14:27:39 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	buf[PATH_MAX];
	char	*res;

	res = NULL;
	if (!(res = ft_strdup(getcwd(buf, PATH_MAX))))
		exit(-1);
	if (res)
		return (res);
	return (NULL);
}

int		ms_pwd(void)
{
	char	*path;

	path = get_pwd();
	if (path)
	{
		ft_putendl_fd(path, 1);
		free(path);
		return (0);
	}
	else
		return (1);
}
