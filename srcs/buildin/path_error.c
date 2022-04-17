/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:38:41 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/28 16:42:43 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		get_error_msg(char *path, int ret)
{
	int	fd;
	DIR	*folder;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("shell: ", 2);
	ft_putstr_fd(path, 2);
	if (!(ft_strchr(path, '/')))
		ret = ret_cnf();
	else if (fd == -1 && folder)
		ret = ret_isdir();
	else if (fd == -1 && !folder)
		ret = ret_nofile();
	else if (fd != -1 && folder == NULL)
		ret = ret_perm();
	if (folder)
		closedir(folder);
	if (fd > 0)
		close(fd);
	return (ret);
}

int		ret_cnf(void)
{
	ft_putendl_fd(": command not found", 2);
	return (127);
}

int		ret_isdir(void)
{
	ft_putendl_fd(": Is a directory", 2);
	return (126);
}

int		ret_nofile(void)
{
	ft_putendl_fd(": No such file or directory", 2);
	return (127);
}

int		ret_perm(void)
{
	ft_putendl_fd(": Permission denied", 2);
	return (126);
}
