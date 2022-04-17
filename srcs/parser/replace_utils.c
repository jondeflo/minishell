/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:59:48 by ccaptain          #+#    #+#             */
/*   Updated: 2020/12/28 17:08:02 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*replace_status(char **str, int i, t_ms *ms)
{
	char	*tmp[3];
	char	*status;
	char	*res;

	tmp[0] = new_substr((*str), 0, i);
	tmp[1] = new_substr((*str), i + 2, ft_strlen(*str));
	status = ft_itoa(ms->last_status);
	tmp[2] = ft_strjoin(tmp[0], status);
	res = ft_strjoin(tmp[2], tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(status);
	free(tmp[2]);
	free(*str);
	*str = NULL;
	return (res);
}

char		*replace_to_none(char **str, int *count)
{
	char	*tmp1;
	char	*tmp2;
	char	*res;

	tmp1 = new_substr((*str), 0, count[1]);
	tmp2 = new_substr((*str), count[0], ft_strlen(*str));
	res = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	free(*str);
	*str = NULL;
	count[0] = 0;
	count[1] = 0;
	return (res);
}

char		*replace_utils(char **str, int i, t_ms *ms)
{
	char	*tmp[3];
	char	*res;
	char	*home;

	home = find_home(&(*ms));
	if (!home)
		home = ft_strdup("");
	tmp[0] = new_substr((*str), 0, i);
	tmp[1] = new_substr((*str), i + 1, ft_strlen(*str));
	tmp[2] = ft_strjoin(tmp[0], home);
	res = ft_strjoin(tmp[2], tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(home);
	free(*str);
	*str = NULL;
	return (res);
}

char		*ft_new(char *str, char *val, int a, int b)
{
	char	*new_tmp;
	char	*new;
	char	*tmp[2];

	tmp[0] = new_substr(str, 0, a);
	tmp[1] = new_substr(str, b, ft_strlen(str) - b);
	new_tmp = ft_strjoin(tmp[0], val);
	new = ft_strjoin(new_tmp, tmp[1]);
	free(new_tmp);
	free(tmp[0]);
	free(tmp[1]);
	free(str);
	return (new);
}
