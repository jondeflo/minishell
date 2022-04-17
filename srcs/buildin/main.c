/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:09:56 by jondeflo          #+#    #+#             */
/*   Updated: 2020/12/21 18:15:13 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_prompt(void)
{
	ft_putstr_fd("\e[1;33mshell>>\x1b[0m", 1);
	signal(SIGINT, sh_int_handler);
	signal(SIGQUIT, sh_int_handler);
}

int		main(int ac, char **av, char **env)
{
	t_ms	ms;
	t_list	*tmp;

	init_env(&ms, env, ac, av);
	while (ms.exit == -1)
	{
		do_prompt();
		if (ms.exit == -1)
		{
			ms.error = begin(&ms);
			if (ms.error == 1)
				clear_list(&ms.queue);
			while (ms.queue && ms.error == 0)
			{
				ms.cmd_list = ms.queue->content;
				while (ms.exit == -1 && ft_lstsize(ms.cmd_list) > 0)
					exec_cmd(&ms, ms.cmd_list, lst_to_env(&ms));
				tmp = ms.queue;
				ms.queue = ms.queue->next;
				free(tmp);
				tmp = NULL;
			}
		}
	}
	free_exit(&ms);
}
