/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:31:51 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/28 14:57:57 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_env_val(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[i]) == 1)
		return (print_err_msg(str));
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
			return (print_err_msg(str));
		i++;
	}
	if (i == 0 && str[i] == '=')
		return (print_err_msg(str));
	if (ft_strlen(str) == 0)
		return (print_err_msg(str));
	return (0);
}

char	*env_name(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!(res = new_substr(str, 0, i)))
		exit(-1);
	return (res);
}

char	*env_val(t_ms *ms, char *name, int i)
{
	t_list	*tmp;
	char	*str;
	char	*res;

	tmp = ms->env;
	str = NULL;
	while (tmp && !str)
	{
		if (ft_strncmp(tmp->content, name, ft_strlen(name)) == 0)
		{
			if (!(str = ft_strdup(tmp->content)))
				exit(-1);
		}
		tmp = tmp->next;
	}
	if (str)
	{
		while (str[i] != '=' && str[i] != '\0')
			i++;
		if (!(res = new_substr(str, i + 1, ft_strlen(str) - i)))
			exit(-1);
		free(str);
		return (res);
	}
	return (NULL);
}

void	remove_env(t_list *prev, t_list *current, t_list *next, t_ms *ms)
{
	if (prev == ms->env)
		ms->env = next;
	current->next = next;
	free(prev->content);
	free(prev);
}

int		ms_unset(t_ms *ms, char **args, int i)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;
	char	*prev_name;
	char	*env;

	while (args && args[i])
	{
		prev = ms->env;
		current = ms->env;
		env = env_name(args[i]);
		while (prev)
		{
			next = (*prev).next;
			prev_name = env_name(prev->content);
			if (ft_strcmp(prev_name, env) == 0)
				remove_env(prev, current, next, &(*ms));
			free(prev_name);
			current = prev;
			prev = next;
		}
		free(env);
		i++;
	}
	return (0);
}
