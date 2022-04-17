/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:24:43 by ccaptain          #+#    #+#             */
/*   Updated: 2020/12/23 15:01:29 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				ft_check_errors(int c, int space)
{
	if (c == ';')
	{
		space == 0 ?
			ft_putstr_fd("syntax error near unexpected token `;;' \n", 1) :
			ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
		return (1);
	}
	else if (c == '|')
	{
		space == 0 ?
			ft_putstr_fd("syntax error near unexpected token `||'\n", 1) :
			ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
		return (1);
	}
	else
		return (0);
}

int				ft_check_begin(char *in)
{
	if (in[0] == ';')
	{
		in[1] == ';' ?
			ft_putstr_fd("syntax error near unexpected token `;;'\n", 1) :
			ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
		return (1);
	}
	else if (in[0] == '|')
	{
		in[1] == '|' ?
			ft_putstr_fd("syntax error near unexpected token `||'\n", 1) :
			ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
		return (1);
	}
	else
		return (0);
}

int				ft_check(char *in, int *i, int quote, int dquote)
{
	int		space;
	int		sym;

	space = 0;
	sym = 0;
	if ((in[*i] == ';' || in[*i] == '|') && (!quote && !dquote))
	{
		while (in[++(*i)] && in[*i + 1] != '\0' &&
			(in[*i] != ';' && in[*i] != '|'))
		{
			if (in[*i] == ' ')
				space++;
			sym++;
		}
		if (space == sym)
		{
			ft_check_errors(in[*i], space);
			return (1);
		}
	}
	return (0);
}

char			*ft_one_more_check(char *in, char *in2)
{
	char		*in3;

	if (in2 != NULL)
	{
		in3 = ft_strjoin("| ", in2);
		free(in2);
		in2 = ft_strjoin(in, in3);
		free(in3);
	}
	return (in2 != NULL ? in2 : in);
}

char			*ft_one_more_check_in(char *in)
{
	char		*in2;
	int			i;

	i = -1;
	in2 = NULL;
	while (in[++i])
	{
		if ((in[i] == '|' || in[i] == ';') && in[i + 1] == '\0')
		{
			if (in[i] == '|')
			{
				ft_putstr_fd("> ", 1);
				ft_read_cmd(&in2);
			}
			in[i] = ' ';
			break ;
		}
	}
	return (ft_one_more_check(in, in2));
}
