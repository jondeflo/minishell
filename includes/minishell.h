/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:30:32 by ccaptain          #+#    #+#             */
/*   Updated: 2021/01/04 16:35:33 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdio.h>

typedef struct	s_cmd
{
	char		**args;
	char		*infile;
	char		*outfile;
	int			rewrite;
	int			flag;
	int			ac;
	char		*cmd;
}				t_cmd;

typedef struct	s_exec
{
	int			tmpin;
	int			tmpout;
	int			fdin;
	int			fdout;
	int			err;
	int			cmd_num;
	char		*path;
	int			fdpipe[2];
	int			i;
	t_cmd		*cmd;
	t_list		*tmp;
}				t_exec;

typedef struct	s_quote
{
	int			one;
	int			two;
	int			f_one;
	int			f_two;
	int			j;
}				t_quote;

typedef struct	s_ms
{
	t_list		*env;
	t_list		*queue;
	t_list		*cmd_list;
	int			last_status;
	int			exit;
	int			error;
	pid_t		pid;
	t_cmd		*cmds;
}				t_ms;

/*
** PARSER
*/

int				ft_check_errors(int c, int space);
int				ft_check_begin(char *in);
int				ft_check(char *in, int *i, int quote, int dquote);
char			*ft_one_more_check(char *in, char *in2);
char			*ft_one_more_check_in(char *in);
char			*ft_get_env_by_key(char *var, char **env, int i, char *tmp);
char			*replace_empty_var(char *str, t_ms *ms, int *count);
char			*ft_replacer(char *str, char *key, char **split, t_ms *ms);
char			*replace_home(char *str, t_ms *ms, size_t i, int q);
char			*ft_replace(char *str, t_ms *ms);
char			*get_empty_var(t_ms *ms, char *str, int *count);
t_quote			quote_init(t_quote *q);
char			*find_home(t_ms *ms);
void			closed(void);
void			ft_decode_cmd(char *cmd);
int				check_begin_redir(char *cmd);
t_cmd			*get_args(char *cmd, t_ms *ms);
t_cmd			**get_commands(char *com, t_ms *ms, int i);
void			parce_cmd(char *com, t_ms *ms);
int				parce_in(t_ms *ms, char *in);
void			init_split_args(int *cnt);
void			init_cnt(int *cnt);
int				ft_set_flag(char *arg, t_cmd *cmd);
void			ft_output(t_cmd *cmd, char *arg);
void			ft_input(t_cmd *cmd, char *arg);
void			ft_rewrite(t_cmd *cmd, char *arg);
void			parce_out(t_cmd *cmd, int i);
void			ft_init_cmd(t_cmd *cmd);
int				ft_free_arr(char **arr);
char			*new_substr(char const *s, unsigned int start, size_t len);
char			**make_pipe_arr(char *str);
int				symbol_skip(char *str, int i, char c);
int				pipe_quote_skip(char *str, int i);
char			**split_by_pipes(char *str, int *cnt);
char			*add_space(char *str, int *cnt);
char			*remove_backslash(char *str, int *cnt);
char			*delete_quote(char **str, int i);
char			*delete_file_quote(char **str, int i);
char			*return_file_name(char *cmd);
char			*remove_quotes(char *cmd, size_t i);
char			*remove_file_quotes(char *cmd, size_t i);
char			*remove_doublespace(char *str, int *c);
void			plus_cnt_two(int *cnt);
void			plus_cnt_one(int *cnt);
void			case_one(char *str, char *tmp, int *cnt);
void			case_two(char *str, char *tmp, int *cnt);
void			case_three(char *str, char *tmp, int *cnt);
void			check_q1_q2(char *str, int *cnt);
int				check_special(char *str, int i);
int				check_special_one(char *str, int *cnt);
int				check_special_two(char *str, int *cnt);
size_t			one_more_skip(char *str, char ch);
char			*replace_status(char **str, int i, t_ms *ms);
char			*replace_to_none(char **str, int *count);
char			*replace_utils(char **str, int i, t_ms *ms);
char			*ft_new(char *str, char *val, int a, int b);
int				check_jackdaw(char *arg);
int				ft_check_in(char *in, t_ms *ms);
int				begin(t_ms *ms);
int				skip_quote_s(char *str, int i);
int				skip_till_next(char *str, int i);
void			skip_space_quote(char *str, int *count);
int				skip_symbols(char *str, int i);
void			reset_count(int *count);
int				skip_char(char *str, int i);
char			*fill_split(char *str, int i);
char			**split_args(char *str, int *cnt, int t, char **split);
char			**make_split_arr(int elem);
char			*sub_str(char **s, int start, int len);
char			*sub_str_1(char **s, int start, int len, int *cnt);
char			**split_by_groups(char *str, int *cnt);
void			plus_cnt_three(int *cnt);
char			**get_group_arr(char *str);
int				count_groups(char const *str);
char			**get_split_arr(char *str, int q1, int q2, int i);
char			*str_join(char **s, char const *s1);
char			*read_line(char *line);
void			ft_read_cmd(char **line);
int				skip_char_1(char *str, int i);
int				skip_char_2(char *str, int i);
int				extended_flag(char *s, int i);
int				ret_fl(char *s, int i);
void			n_input(t_cmd *cmd, int i);
void			n_rewrite(t_cmd *cmd, int i);
void			n_output(t_cmd *cmd, int i);
void			n_remove_redirect(t_cmd *cmd, int k);
char			*n_delete_file_quote(char **str, int i);
char			*n_remove_file_quotes(t_cmd *cmd, int k, size_t i);
void			make_in_out(t_cmd *cmd, int i);
void			make_rewrite(t_cmd *cmd, int i);
void			make_redir(t_cmd *cmd, int i);
void			n_remove_redirect(t_cmd *cmd, int k);
void			n_remove_one_arg(t_cmd *cmd, int i, int k, int j);
void			n_remove_two_args(t_cmd *cmd, int i, int k, int j);
void			free_cmd_arr(t_cmd *cmd);
void			norme_pleasurer(char *str, int *cnt);

/*
** BUILD
*/

int				is_buildin(char *cmd);
int				exec_buildin(t_ms *ms, char **args);
void			cd_err(char **args);
int				add_pwd_path(t_ms *ms, char *pwd, char *path);
int				get_pwd_path(t_ms *ms, char *abspath);
void			add_normal_path(t_ms *ms, char *pwd);
int				ms_cd(t_ms *ms, char **args);
int				exec_prepare(t_exec *exec, char **env, t_ms *ms);
void			exec_next(t_exec *exec);
void			finish_exec(t_exec *exec, t_ms *ms, char **env);
void			init_exec(t_exec *exec, t_list *cmd_list);
void			make_pipe(t_exec *exec);
int				exec_cmd_end(t_exec *exec, t_ms *ms, char **env);
int				fork_error(t_ms *ms);
void			make_fork(t_ms *ms);
void			pre_exec_buildin(t_ms *ms, t_exec *exec);
void			pre_exec_alien(t_exec *exec, char **env);
int				exec_open_in_err(t_ms *ms, t_exec *exec);
int				exec_open_out_err(t_ms *ms, t_exec *exec);
int				exec_out(t_exec *exec, t_ms *ms);
void			exec_replace(t_exec *exec, t_ms *ms);
int				check_stat(char *path);
int				ms_export(t_ms *ms, char **args);
int				print_empty_export(t_ms *ms);
void			ft_list_sort(t_list **begin_list);
int				add_env(t_ms *ms, char *str);
int				print_err_msg(char *str);
int				is_number(char *str);
int				ms_exit(t_ms *ms, char **args);
int				ms_env(t_ms *ms);
int				ms_echo(char **args);
void			free_exit(t_ms *ms);
void			fill_queue(t_ms *ms);
char			**copy_arr(char **av);
void			fill_cmd_list(t_ms *ms, t_cmd *src);
void			clear_list(t_list **begin_list);
char			**lst_to_env(t_ms *ms);
void			init_env(t_ms *ms, char **env, int ac, char **av);
int				the_main_fn(t_ms *ms, t_exec *exec, char **env);
int				exec_cmd(t_ms *ms, t_list *cmd_list, char **env);
int				main(int ac, char **av, char **env);
char			*find_path(char *path, char *prog);
char			**get_env_path(char **env, int i);
char			*get_cmd_path(char *path, char **env, int i);
int				get_error_no(t_ms *ms, char *path);
int				get_error_msg(char *path, int ret);
int				ret_cnf(void);
int				ret_isdir(void);
int				ret_nofile(void);
int				ret_perm(void);
char			*get_pwd(void);
int				ms_pwd(void);
void			sh_int_handler(int sgnl);
void			cmd_int_handler(int sgnl);
void			sig_filler(t_ms *ms, int err);
int				check_env_val(char *str);
char			*env_name(char *str);
char			*env_val(t_ms *ms, char *name, int i);
void			remove_env(t_list *prev, t_list *current,
					t_list *next, t_ms *ms);
int				ms_unset(t_ms *ms, char **args, int i);

#endif
