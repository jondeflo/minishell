/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:51:57 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/04 12:31:15 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char *path, char *prog)
{
	DIR				*folder;
	struct dirent	*entry;
	char			*tmp;
	char			*res;

	folder = opendir(path);
	if (folder == NULL)
		return (ft_strdup("Unable to read directory"));
	while ((entry = readdir(folder)))
	{
		if (ft_strcmp(entry->d_name, prog) == 0)
		{
			closedir(folder);
			if (!(tmp = ft_strjoin("/", prog)))
				exit(-1);
			if (!(res = ft_strjoin(path, tmp)))
				exit(-1);
			free(tmp);
			return (res);
		}
	}
	closedir(folder);
	return (0);
}

char	**get_env_path(char **env, int i)
{
	char	*str;
	char	*tmp;
	char	**spl;

	str = NULL;
	spl = NULL;
	while (env[i] && !str)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			str = env[i];
		i++;
	}
	if (str)
	{
		tmp = new_substr(str, 5, ft_strlen(str) - 5);
		spl = ft_split(tmp, ':');
		free(tmp);
	}
	if (spl)
		return (spl);
	return (NULL);
}

char	*get_cmd_path(char *path, char **env, int i)
{
	char	*newpath;
	char	**spl;

	newpath = NULL;
	spl = get_env_path(env, 0);
	if (spl)
	{
		while (spl[i] && !newpath)
		{
			newpath = find_path(spl[i], path);
			i++;
		}
		i = 0;
		while (spl[i])
			free(spl[i++]);
		free(spl);
	}
	if (newpath)
		return (newpath);
	return (ft_strdup(path));
}

int		get_error_no(t_ms *ms, char *path)
{
	int	fd;
	DIR	*folder;
	int	ret;

	ret = 0;
	fd = open(path, O_WRONLY);
	folder = opendir(path);
	if (!(ft_strchr(path, '/')))
		ret = 127;
	else if (fd == -1)
	{
		if (folder)
			ret = 126;
		if (!folder)
			ret = 127;
	}
	else if (fd != -1 && folder == NULL)
		ret = 126;
	if (folder)
		closedir(folder);
	if (fd > 0)
		close(fd);
	ms->last_status = ret;
	return (ret);
}
