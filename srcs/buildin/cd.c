/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:47:44 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/04 11:09:31 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		cd_err(char **args)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(args[1], 2);
	}
	else if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
		ft_putendl_fd("shell: cd: HOME not set", 2);
	else if (ft_strcmp(args[1], "-") == 0)
		ft_putendl_fd("shell: cd: OLDPWD not set", 2);
	else
	{
		ft_putstr_fd("cd: No such file or directory: ", 2);
		ft_putendl_fd(args[1], 2);
	}
}

int			add_pwd_path(t_ms *ms, char *pwd, char *path)
{
	int		ret;
	char	*tmp1;
	char	*tmp2;

	ret = chdir(path);
	if (!(tmp1 = ft_strjoin("OLDPWD=", pwd)))
		exit(-1);
	free(pwd);
	pwd = get_pwd();
	if (!(tmp2 = ft_strjoin("PWD=", pwd)))
		exit(-1);
	add_env(&(*ms), tmp1);
	add_env(&(*ms), tmp2);
	free(tmp1);
	free(tmp2);
	free(pwd);
	return (ret);
}

int			get_pwd_path(t_ms *ms, char *abspath)
{
	int		ret;
	char	*path;
	char	*pwd;

	ret = 0;
	pwd = get_pwd();
	path = env_val(&(*ms), abspath, 0);
	if (pwd && path)
	{
		ret = add_pwd_path(&(*ms), pwd, path);
		free(path);
	}
	else
	{
		ret = 1;
		if (pwd)
			free(pwd);
	}
	return (ret);
}

void		add_normal_path(t_ms *ms, char *pwd)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp_pwd;

	if (!(tmp1 = ft_strjoin("OLDPWD=", pwd)))
		exit(-1);
	tmp_pwd = get_pwd();
	if (!(tmp2 = ft_strjoin("PWD=", tmp_pwd)))
		exit(-1);
	add_env(&(*ms), tmp1);
	add_env(&(*ms), tmp2);
	free(tmp1);
	free(tmp2);
	free(tmp_pwd);
}

int			ms_cd(t_ms *ms, char **args)
{
	int		ret;
	char	*pwd;

	ret = 0;
	pwd = get_pwd();
	if (!args[1] || ft_strcmp(args[1], "~") == 0 ||
			ft_strcmp(args[1], "--") == 0)
		ret = get_pwd_path(&(*ms), "HOME");
	else if (ft_strcmp(args[1], "-") == 0)
		ret = get_pwd_path(&(*ms), "OLDPWD");
	else
	{
		ret = chdir(args[1]);
		if (ret == 0)
			add_normal_path(&(*ms), pwd);
	}
	if (pwd)
		free(pwd);
	if (ret == -1)
		ret = 1;
	ms->last_status = ret;
	if (ret != 0)
		cd_err(args);
	return (ret);
}
