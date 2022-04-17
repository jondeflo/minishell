/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 14:49:12 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/23 15:08:01 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_join(char **s, char const *s1)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!(res = malloc(sizeof(char) * (ft_strlen(*s) + ft_strlen(s1) + 1))))
		exit(-1);
	while ((*s)[j] != '\0')
		res[i++] = (*s)[j++];
	j = 0;
	while (s1[j] != '\0')
		res[i++] = s1[j++];
	res[i] = '\0';
	free(*s);
	*s = NULL;
	return (res);
}

char	*read_line(char *line)
{
	char	buf[2];
	char	**ptr;

	ptr = &line;
	buf[0] = '\0';
	buf[1] = '\0';
	while (buf[0] != '\n')
	{
		*ptr = str_join(&line, buf);
		while ((read(0, buf, 1)) == 0)
		{
			ft_putstr_fd("  \b\b", 1);
			if (ft_strlen(line) == 0)
				exit(-1);
		}
	}
	return (line);
}

void	ft_read_cmd(char **line)
{
	*line = ft_strdup("");
	*line = read_line((*line));
}
