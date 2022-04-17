/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:33:06 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/21 11:36:30 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	plus_cnt_two(int *cnt)
{
	cnt[2] += 2;
	cnt[3]++;
}

void	plus_cnt_one(int *cnt)
{
	cnt[2]++;
	cnt[3]++;
}

void	case_one(char *str, char *tmp, int *cnt)
{
	tmp[cnt[3]] = str[cnt[2]];
	plus_cnt_two(cnt);
}

void	case_two(char *str, char *tmp, int *cnt)
{
	tmp[cnt[3]] = str[cnt[2] + 1];
	plus_cnt_two(cnt);
}

void	case_three(char *str, char *tmp, int *cnt)
{
	tmp[cnt[3]] = str[cnt[2]];
	plus_cnt_one(cnt);
}
