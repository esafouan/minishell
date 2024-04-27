/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kremidi <kremidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:56:22 by kremidi           #+#    #+#             */
/*   Updated: 2023/03/23 00:12:21 by kremidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct trim
{
	char			*tmp;
	int				i;
	int				j;
}					t_trim;

typedef struct t_global
{
	int				g_status;
	int				ex;
	int				*l_fd;
}					t_global;

t_global			g_gbl;

typedef struct quote
{
	int				i;
	int				j;
	int				k;
	int				j1;
	char			c;
	char			*tmp;
	char			*tmp1;
	char			*src;
	char			*exp;
}					t_q;

typedef struct s_env
{
	char			*data;
	int				j;
	struct s_env	*next;
	int				cmd_count;
}					t_env;

typedef struct t_fd
{
	int				fd1;
	int				fd2;
	int				i;
	int				x;
	int				tmpin;
	int				tmpout;
	char			**env;
	char			*path;
	int				**fd_hd;
	int				j;
	int				y;
	int				z;
	int				var;
	t_env			**envfr;
	int				quote;
}					t_fd;

typedef struct input
{
	int				count;
	int				i;
	int				k;
	int				j;
	int				check;
	char			*new;
	int				flag;
}					t_inp;

typedef struct s_here
{
	int				fd;
	struct s_here	*next;
}					t_here;

typedef struct split
{
	int				count;
	int				len;
	char			*cpystring;
	int				a;
	int				skip;
	int				num_word;
	int				c;
	int				j;
	int				b;

}					t_split;

typedef struct s_hleper
{
	int				j;
	int				b;
	int				i;
	int				c;
	char			*tempo;
	int				for_skip_cmd;
	char			**cmd;
	char			**in;
	char			**out;
	char			**split;
	int				pour;
	char			*input;
}					t_help;

typedef struct t_pars
{
	char			**command;
	char			**file;
	struct t_pars	*next_command;
	int				fds[2];
	int				id;
	int				fd;
	int				h;
	int				checker;
	int				exit;
	char			**env;

}					t_pars;

void				handle_sigint(int sig);
void				handle_sigint2(int sig);
int					helper_norm(char c);
int					helper_norm2(char c);
void				ft_finito_export(t_env **env, t_pars *parsing, int *x,
						int *i);
int					number_cmd(t_pars **mini);
int					ft_hd2(t_pars **mini, t_fd *forces);
void				rl_replace_line(const char *str, int undo);
char				*ft_free(char *s1, char *s2);
char				*ft_strjoin1(char *s1, char *s2);
char				*ft_strcpy(char *s1, char *s2);
char				*ft_strcat(char *dest, char *src);
char				*ft_strjoin(char *s1, char *s2);
char				**ft_split(char *s);
int					ft_strlen(char *s);
char				*ft_strcpy(char *s1, char *s2);
char				*ft_substr(char *s1, int start, int len);
//void				*ft_calloc(size_t count, size_t size);
void				*ft_calloc(int count, int size);
void				free_split(char **split);
int					ft_atoi_fd(char *str);
char				*get_all(char *str, int fd);
char				*get_line(char *str1, int *i);
char				*get_rest(char *rmdr, int *i);
char				*get_next_line(int fd);
t_pars				*ft_lstlast(t_pars *lst);
t_env				*ft_lstlast2(t_env *lst);
void				ft_lstadd_back(t_env **lst, t_env *new);
void				ft_lstadd_front(t_env **lst, t_env *new);
t_pars				*ft_lstnew(t_help *pars);
t_env				*ft_lstnew2(char *content);
int					ft_lstsize(t_env *lst);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *str, int fd);
void				ft_putstr_fd(char *str, int fd);
int					ft_strchr_fd(char *str, char c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strjoin(char *s1, char *s2);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
int					ft_strlen(char *str);
int					ft_strncmp(char *s1, char *s2, int n);
void				add_new_env(t_env **env, char *content);
int					ft_parssplit(char *str);
void				ft_sort_list(t_env **env);
char				*ft_old_pwd(t_env **env, char *str);
int					ft_cd_utils(t_env **env, char *oldpwd, char *pwd);
int					ft_cd_handler(t_env **env, char *str);
int					if_pwd_noexist(t_env **env);
int					ft_cd(t_env **env, t_pars *parsing);
int					ft_echo_utils(char *str);
int					ft_echo(t_pars *parsing);
void				ft_heredoc(char *s, t_fd *forces, t_pars *mini, int *fd);
void				convert(t_env **env, char **str);
int					ft_env(t_env **env);
int					is_num(char *str);
int					ft_print_error(char *command, char *str, char *msg);
void				ft_exit(t_pars *parsing);
void				ft_declare(t_env **env);
int					ft_check_export(char *str);
int					ft_if_exist(t_env **env, char *str);
char				*mystrcpy(char *str);
void				ft_edit(t_env **env, char *str, int *n);
int					ft_export(t_env **env, t_pars *parsing);
int					ft_pwd(void);
int					search_home(t_env **env);
int					ft_get_var(char *str);
void				ft_remove_if(t_env **env, char *str);
int					ft_unset(t_env **env, t_pars *parsing);
char				*ft_strc(char *str);
int					ft_if_exist2(t_env **env, char *str);
int					getvar(char *str);
int					ft_exec_builtins(t_env **envir, t_pars *mini, t_fd *forces);
int					ft_cd_double(char *str);
int					ft_cd_ext(t_env **env, char *str);
int					ft_strncmp2(char *s1, char *s2, int n);
int					ft_get_home(t_env **env);
int					cd_home(t_env **env, char *str);
void				change_it(t_env **env, char *str, char *pwd);
int					ft_hd1(t_pars **mini, t_fd *forces);
int					checker(t_pars **mini);
void				exp_env(t_pars *mini, t_env **env);
char				**expanding_utils(t_env **env, t_pars *mini);
char				*help_expanding(char *str, int j, char *env, char **envir);
char				*expanding(char *str, char **env);
int					search_exp(char *input, char *env);
int					count_variables(char *input);
char				*help_fill_exp(char *split, int j, char **env);
char				*fill_exp(char *str, char **env);
void				ft_putstr_here(char *str, int fin, int fd, t_pars *mini);
void				ft_puthere(char *str, int fd, t_pars *mini);
void				init_minishell(t_env *envir, t_fd *forces, t_help *pars,
						t_pars *mini);
void				minishell(t_env **envir, t_fd *forces, t_pars *mini);

void				piping_hd(t_fd *forces, t_pars **mini);
int					ft_number_hd(t_pars **mini);
void				freeing(t_fd *forces, t_pars **mini);
void				closing_hd(t_fd *forces, t_pars **mini);
void				ft_exec_builtins1(t_pars *mini, t_fd *forces);
void				ft_exec_builtins2(t_fd *forces);
void				ft_exec_builtins3(t_env **envir, t_pars *mini);
void				exp1(t_fd *forces, t_pars **mini, t_pars *temp);
t_pars				*parser(t_pars *mini, t_help *pars, char **split);

char				*ft_strdup(char *s1);
char				*ft_itoa(int n);
void				lexer_expander(t_env **env, t_fd *forces, t_help *pars);
int					checkegal(char *str);
int					exec_process(t_env **envir, t_pars **mini, t_fd *forces);
int					check_builtin(t_pars *mini);
char				*find_path(char *cmd, t_env **envir);
char				*find_value(char *key, t_env **envir);

void				exec_child_process(t_pars *mini, t_env **env, t_fd *forces,
						int fds[2]);
void				ft_exit_finito(t_pars *parsing);
void				ft_error(char *command, char *str);
char				**convert_tab(t_env **env, char **envir);
int					exec_path(t_env **envir, t_pars **mini, t_fd *forces);
int					ft_file(t_pars **mini, t_fd *forces);
int					ft_infile(char *str, t_fd *forces);
int					ft_append(char *str, t_fd *forces);
int					ft_outfile(char *str, t_fd *forces);
int					ft_check_redirection(char *str);
int					ff1(t_pars **mini, t_fd *forces);
int					ft_hd(t_pars **mini, t_fd *forces);
void				id_cmd(t_pars **mini);
int					num_cmd(t_pars **mini);
int					*tab_pipe(t_pars **mini, int i);
int					check_hd(char *str);
void				first_child(t_pars *temp, t_fd *forces);
void				mid_child(t_pars *temp, t_fd *forces);
void				last_child(t_fd *forces);
void				parent_process(t_pars *temp, t_pars **mini);
void				exec_process_utils(t_pars *temp, char **env, char *path);
void				init_exec_process(t_fd *forces, t_pars **mini);
void				ft_my_putstr(char *str, int fin, int fd);
void				exec_path_utils(t_pars **mini);
void				exec_path_utils2(t_fd *forces, t_pars **mini);
void				exec_path_utils3(t_fd *forces, t_pars **mini, char **env,
						char *path);

char				*ft_itoa(int n);
char				*ft_strdup(char *s1);
char				*ft_strlcpy1(char *dst, char *src, int dstsize);
char				*expander(char *input, t_env **env, t_fd *forces);
int					syntax_error_quote(char *input, t_inp *inp);
int					first_check(char *input);
int					syntax_error_pipe(char **string, char *input);
int					syntax_error_out_red(char **string);
int					syntax_error_in_red(char **string);
char				*help_fill_variables(char *split, int j, t_env **env,
						t_fd *forces);
void				fill_variables(t_help *pars, t_env **env, t_fd *forces);
int					ft_strlen(char *s);
char				**get_redirection(t_help *pars);
char				**final_cmd(t_help *pars);
int					get_command(char **string, t_help *pars);
t_pars				*ft_lstnewpars(t_help *pars);
t_pars				*ft_lstlastpars(t_pars *lst);
void				ft_lstadd_backpars(t_pars **lst, t_pars *new);
char				*ft_strtrim(char *s1, char *set);
int					checking(char *str);
char				**empty_string(void);
int					ft_check_redirection1(char *str);
int					check_space(char *str);
void				ft_file2(int fd, int *check);
void				ft_cd_ext2(char *str, char *pwd);
void				ft_cd_ext3(char *str, char *pwd);
int					count_word1(char *s1, char c);
int					count_len1(char *s1, char c);
char				*free_split1(char **split, int len);
void				ft_cpysplit1(char *s, char **split, char c);
char				**ft_split2(char *s, char c);
void				ft_pordgrass(char **env);
void				ft_pordgrass2(char **env, pid_t *pid, char *path);
char				*help_quotes(char *input, char *envirement);
int					count_qoutes(char *input);
int					count_variables(char *input);
char				*handle_qoute(char *input);
int					check_qoute(t_fd *forces, char *input);
void				stingbefor_quote(t_split *help);
int					skiper(char *p, char x, t_split *help);
void				help_skiper(char *p, char x, t_split *help);
char				**final_cmd(t_help *pars);
char				**final_file(t_help *pars);
char				*get_ready_input(char *input, t_inp *inp);
t_pars				*trim_midle_commands(t_trim *trim, t_pars **mini);
t_pars				*trim_midle_files(t_trim *trim, t_pars **mini);
t_pars				*parser(t_pars *mini, t_help *pars, char **split);
int					ft_count_cmd(char **s1, char s);
void				free_all(t_pars *mini, t_help *pars);
void				free_list(t_pars *mini);
t_env				*ft_lstnew333(char *content);
int					index_of_var(char *input);
char				*first_variable(char *envirement, char *input, t_env **env,
						t_fd *forces);
int					search(char *input, t_env **env);
char				*expander_helper(char *envirement, char *input, t_env **env,
						t_fd *forces);
char				*help_envirement(char *input, int j, t_env **env,
						t_fd *forces);
char				*help_envirement3(char *input, int j);
char				*exit_status_alphanum(char *envirement, char *input,
						t_env **env, t_fd *forces);
char				*help_envirement2(char *input, int j, t_env **env,
						t_fd *forces);
int					is_alpha_num(int c);
char				*space_inside_quotes(char *input, int j, t_env **env,
						t_fd *forces);
void				norm(t_help *pars, t_env **env, t_fd *forces);
int					count_variables(char *input);
int					var_check(char *input);
void				lexer_expander(t_env **env, t_fd *forces, t_help *pars);
void				lexer_expander_helper(t_env **env, t_fd *forces,
						t_help *pars, t_inp *inp);
t_pars				*last_trim(t_pars *mini, t_help *pars, t_trim *trim);
int					syntax_error_red(char *input, t_inp *inp);
int					syntax_error_red_infile(char *input, t_inp *inp);
void				syntax(t_help *pars, t_inp *inp);
void				norm_exec(char **env, char *path, pid_t *pid);
void				ftn(t_pars *temp, int *i);
int					ft_rmv(char *curr, char *str);
void				ft_hd1_nor(void);
int					first_ret(char **env, t_pars *temp);
int					second_ret(pid_t *pid, char **env);
int					ft(t_pars *temp, t_fd *forces, t_env **envir,
						t_pars **mini);
void				ex_pr(t_env **envir, t_pars **mini, t_fd *forces,
						t_pars *temp);
t_pars				*ex_pr1(t_pars **mini);
t_pars				*ex_pr3(pid_t *pid, t_pars *temp, t_pars **mini,
						char *path);
void				nor(t_pars **mini);
int					is_this(char c);
void				norm_put(int *fin, int *start, int *check);
void				normani(int *i, int *check);
int					cd_ret(t_env *temp);
void				single_odd(t_help *pars, t_fd *forces, t_q *q);
void				single_even(t_help *pars, t_env **env, t_fd *forces,
						t_q *q);
void				skip_in_single(t_help *pars, int c, t_fd *forces, t_q *q);
void				single(t_help *pars, t_env **env, t_fd *forces, t_q *q);
void				doublq_counter(t_help *pars, t_fd *forces, t_q *q);
void				norm(t_help *pars, t_env **env, t_fd *forces);
int					counter_single_quotes(char *input);
void				init_var(char *input, t_inp *inp);
void				elsee(char *input, t_inp *inp);
int					for_syntx(char *input, t_inp *inp);
void				quote(t_help *pars, t_env **env, t_fd *forces);
int					allocate__new_string(char *input);
void				mini_count(t_split *help, char c);
char				*return_space(t_trim *trim);

#endif
