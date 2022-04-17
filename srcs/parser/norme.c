/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:01:30 by jondeflo          #+#    #+#             */
/*   Updated: 2021/01/04 16:34:59 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		skip_char(char *str, int i)
{
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

char	**make_split_arr(int elem)
{
	char	**split;

	if (!(split = (char **)malloc(sizeof(char *) * (elem + 1))))
		exit(-1);
	split[elem] = NULL;
	return (split);
}

char	*sub_str_1(char **s, int start, int len, int *cnt)
{
	char	*res;
	int		i;

	i = 0;
	if (start > len)
		len = 0;
	if (!(res = malloc(sizeof(char) * (len + 1))))
		exit(-1);
	while (i < len && (*s)[start] != '\0')
	{
		res[i] = (*s)[start];
		i++;
		start++;
	}
	res[i] = '\0';
	free(*s);
	*s = NULL;
	cnt[2] = 0;
	return (res);
}

void	norme_pleasurer(char *str, int *cnt)
{
	char	tmp;

	tmp = str[cnt[2]];
	cnt[2]++;
	while (str[cnt[2]] && (str[cnt[2]] != tmp))
		cnt[2]++;
	if (str[cnt[2]])
		cnt[2]++;
}
