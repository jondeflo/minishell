/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:29:29 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/20 14:52:19 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*get_empty_var(t_ms *ms, char *str, int *count)
{
	reset_count(count);
	return (replace_empty_var(str, &(*ms), count));
}

t_quote		quote_init(t_quote *q)
{
	q->one = 0;
	q->two = 0;
	q->f_one = 0;
	q->f_two = 0;
	q->j = -1;
	return (*q);
}

char		*find_home(t_ms *ms)
{
	int		i;
	char	**env;
	char	*tmp;

	i = 0;
	env = lst_to_env(&(*ms));
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME", 4) == 0)
		{
			tmp = new_substr(env[i], 5, ft_strlen(env[i]));
			ft_free_arr(env);
			return (tmp);
		}
		i++;
	}
	ft_free_arr(env);
	return (NULL);
}
