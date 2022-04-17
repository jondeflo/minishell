/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:09:19 by ccaptain          #+#    #+#             */
/*   Updated: 2021/01/04 15:53:05 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*ft_get_env_by_key(char *var, char **env, int i, char *tmp)
{
	char	**new;
	char	*key;

	key = ft_strjoin(var, "=");
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			new = ft_split(env[i], '=');
			if (new[0] && new[1])
			{
				if (ft_strcmp(new[0], var) == 0)
					tmp = ft_strdup(new[1]);
				ft_free_arr(new);
				free(key);
				key = NULL;
			}
		}
		if (tmp)
			break ;
		i++;
	}
	free(key);
	ft_free_arr(env);
	return ((tmp) ? tmp : ft_strdup(""));
}

char		*replace_empty_var(char *str, t_ms *ms, int *count)
{
	char	**ptr;

	ptr = &str;
	while (count[0] < (int)ft_strlen(str))
	{
		count[0] = skip_quote_s(str, count[0]);
		if (str[count[0]] == '\'')
			count[0] = skip_till_next(str, count[0]);
		if (count[0] < (int)ft_strlen(str) && str[count[0]] == '$')
		{
			if (str[count[0] + 1] && str[count[0] + 1] == '?')
			{
				*ptr = replace_status(&str, count[0], &(*ms));
				reset_count(count);
			}
			else
			{
				skip_space_quote(str, count);
				*ptr = replace_to_none(&str, count);
			}
		}
		else
			count[0]++;
	}
	return (str);
}

char		*ft_replacer(char *str, char *key, char **split, t_ms *ms)
{
	t_quote	q;
	char	*val;

	q = quote_init(&q);
	while ((ft_strlen(str) > 0) && str[++q.j])
	{
		str[q.j] == '\'' ? q.one++ : q.one;
		str[q.j] == '\'' && q.two == 0 && q.one == 1 ? q.f_one++ : q.f_one;
		str[q.j] == '"' ? q.two++ : q.two;
		str[q.j] == '"' && q.one == 0 && q.two == 1 ? q.f_two++ : q.f_two;
		if (!ft_strncmp((str + q.j), key, ft_strlen(key)) &&
				(!q.one || q.two) && (!q.f_one || q.f_two))
		{
			val = ft_get_env_by_key(split[0], lst_to_env(&(*ms)), 0, NULL);
			str = ft_new(str, val, q.j, q.j + ft_strlen(key));
			free(val);
		}
		q.one == 2 ? q.one = 0 : q.one;
		q.one == 2 ? q.f_one = 0 : q.f_one;
		q.two == 2 ? q.two = 0 : q.two;
		q.two == 2 ? q.f_two = 0 : q.f_two;
	}
	return (str);
}

char		*replace_home(char *str, t_ms *ms, size_t i, int q)
{
	char	**ptr;
	char	tmp;

	ptr = &str;
	while (i < ft_strlen(str))
	{
		i = skip_symbols(str, i);
		if (str[i] == '\'' || str[i] == '"')
		{
			tmp = str[i++];
			q *= -1;
			while (str[i] && (str[i] != tmp))
				i++;
			q *= -1;
			i++;
		}
		if (i < ft_strlen(str) && str[i] == '~')
		{
			*ptr = replace_utils(&str, i, &(*ms));
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

char		*ft_replace(char *str, t_ms *ms)
{
	int		i;
	char	**split;
	char	*key;
	char	**env;
	int		count[2];

	i = 0;
	env = lst_to_env(&(*ms));
	while (env[i])
	{
		split = ft_split(env[i], '=');
		key = ft_strjoin("$", split[0]);
		str = ft_replacer(str, key, split, ms);
		free(key);
		ft_free_arr(split);
		free(env[i]);
		i++;
	}
	free(env);
	if (ft_strchr(str, '$'))
		str = get_empty_var(&(*ms), str, count);
	if (ft_strchr(str, '~'))
		str = replace_home(str, &(*ms), 0, 1);
	return (str);
}
