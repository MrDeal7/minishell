/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:27:14 by adimas-d          #+#    #+#             */
/*   Updated: 2024/11/01 22:34:24 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# define RED		"\033[1;31m"	/*Red color*/
# define YLW		"\033[1;33m"	/*Yellow color*/
# define RST		"\033[0m"		/*Reser color*/
# define PROMPT		"minihell> "
//# define MAX_LINE	80

//int	g_exit_status = 0;

typedef enum e_code
{
	PWD,
	ECHO,
	UNSET,
	EXPORT,
	CD,
	EXIT,
	ENV,
	OTHER
}			t_code;

typedef enum e_token
{
	WORD,
	RD_IN = '<',
	RD_OUT = '>',
	AP_IN,
	AP_OUT,
	PIPE = '|',
	QUOTE = '\'',
	D_QUOTE = '"',
	SPACES = ' ',
	TABS = '\t',
	DOLLAR = '$',
	EQUAL = '=',
	QUESTION = '?'
}			t_token;

typedef enum s_type
{
	CHILD,
	PARENT,
	HERE_DOC,
	IGNORE,
	CLOSE_PIPE
}			t_type;

typedef struct s_command	t_command;

typedef struct s_args
{
	char		**env;
	char		**exp;
	char		**argv;
	int			**token;
	char		*line;
	bool		error;
	int			redirect_count;
	int			apend_count;
	int			pipe_count;
	bool		exit;
	int			exit_code;
	char		**splited;
	t_command	*cmd;
}			t_args;

typedef struct s_command
{
	char		**args;
	char		**redir;
	char		*line;
	int			input;
	int			output;
	int			ex;
	int			flag;
	t_command	*next;
	int			redir_e;
	char		*temp;
}			t_command;

typedef struct s_pipes
{
	int	pipe_p[2];
	int	pipe_fd[2];
	int	pipe_fd_extra[2];
	int	here_doc_pipe[2];
}			t_pipes;

typedef struct s_exit
{
	int		code;
	t_args	*args;
}			t_exit;

/* built-in.c */
int			ft_pwd(void);
void		ft_echo(char **args, int output);
void		ft_env(char **vars, int output);
void		ft_unset(t_args *args, t_command *cmd);
void		ft_export(t_args *args, t_command *cmd);
void		ft_cd(t_args *args, t_command *cmd, int output);
void		ft_exit(t_args *args, t_command *cmd);
void		ft_new_export_vars(t_args *args);

/* built-in2.c */
void		ft_update_oldpwd(t_args *args);
void		ft_update_pwd(t_args *args);

/* expansions_utils.c */
int			env_name_size(char *line);
int			line_var_name_size(char *line);
int			longer_str(char *line_var, char *env);
char		*env_search(t_args *args, char *line, int size);
int			dollar_expansion_size(t_args *args, char *line);

/* expansions_utils2.c */
int			expansion_size_in_d_quotes(t_args *args, char *line);
int			dollar_expansion(t_args *args, char *line, char *new_str, int j);
int			ft_pid_expand(char *new_str, int j);
int			ft_put_exitcode(t_args *args, char *new_str, int j);
char		*ft_dont_expand(char *line, char *new_str, int *j);

/* expansions_utils3.c */
void		space_for_expansions_helper(t_args *args, char *line, char *temp, \
				int *expan_sz);
char		*space_for_expansions(t_args *args, char *line, int line_sz, \
				int expan_sz);
int			ft_size_of_pid(void);
int			ft_size_of_exitcode(t_args *args);

/* expansions.c */
char		*ft_expand_vars_d_quotes_helper(t_args *args, char *line, \
				char *new_str, int *j);
char		*ft_expand_vars_d_quotes(t_args *args, char *line, char *new_str, \
				int *j);
char		*ft_expand_vars_quotes(char *line, char *new_str, int *j);
char		*ft_expand_vars_helper(t_args *args, char *line, char *new_str, \
				int *j);
char		*ft_expand_vars(t_args *args, char *line);

/* minishell.c */
int			ft_array_sz(char **envp);
t_code		check_line(char *line);
void		ft_clear_cmd_list(t_command **cmd);
void		ft_clear_cmd(t_command *cmd);

/* parse_utils.c */
t_command	*ft_command_lst_start(char	*line);
void		ft_cmd_lst_add_back(t_command **lst, t_command *new);
void		ft_build_cmd_lst(t_args *args, t_command **cmd);
int			ft_need_spaces(char *line, int i);
char		*ft_put_spaces2(char *new, char *line, int *j);

/* parse_utils2.c */
int			str_count(t_args *args, char *str);
void		ft_separated_by_pipe(t_args *args, char **splited, char *line);
void		ft_split_pipes(t_args *args, char *line);
char		*ft_put_spaces_helper(char *new, char *line, int *j);
char		*ft_put_spaces_helper2(char *new, char *line, int *j);

/* parse_utils3.c */
int			ft_count_redirects(char *line, int redirect_count);
int			ft_count_apends(char *line, int apend_count);
int			ft_count_pipes(t_args *args, char *line);
void		ft_count_pipe_redirect(t_args *args, char *line);
char		*ft_put_spaces(char *line, int size, int j);

/* parse_utils4.c */
int			ft_str_sz(char *str, int i);
char		*ft_split_skip(char *str);
void		strings_content2(char **split, char *str, int quotes_on);
char		**ft_split_args(char *str, int quotes_on);
void		ft_expansions(t_args *args);

/* parse.c */
char		*ft_new_spaces_added(char *line, int size);
char		*ft_add_spaces_if_needed(char *line);
void		ft_parsing(t_args *args, t_command **cmd, char *line);

/* pipes.c */
void		function_caller(t_args *args, t_command *cmd);
void		ft_delete_rdir(t_command *cmd);
void		ft_redir_args_helper(t_command *cmd, bool *rdir_flag, char **temp, \
				char *temp2);
char		**ft_redir_args(t_command *cmd, int size);

/* rdir.c */
void		ft_delete_rdir_helper(char **str, int k);

/* signal_utils.c */
void		ft_closepipe(int signal, siginfo_t *si_ha, void *unused);
void		ft_child(int signal, siginfo_t *si_ha, void *unused);
void		ft_sig_int(int signal, siginfo_t *si_ha, void *unused);
t_exit		ft_start_exitcode(t_args *args);
void		ft_exitcode(int code);

/* signal.c */
void		signal_handler(t_type sig);

/* syntax_verify.c */
bool		ft_wrong_nbr_of_quotes(char *line);
bool		ft_wrong_rdir(char **args, int i);
bool		ft_pipe_sytax(char **args, int i);
bool		ft_not_alowed_char(char *arg);
void		ft_syntax(t_args *args, char *line);

/* utils.c */
void		error_exit(char *error);
void		error_print(char *error);
//void		ft_exit_code(t_args *args, int exit_code);
void		ft_sort(char **sort);
void		ft_free_array(char **array);
int			ft_cd_erro(int cd);

/* utils2.c */
int			ft_sz_in_quotes(char *str, char c);
char		*ft_skip_spaces(char *str);
char		*ft_jump_rdir(char *str);
char		**ft_dup_arr(char **arr);
int			ft_copy_until(char *to, char *from, char c, int j);

/* utils3.c */
int			ft_cpy_rdir_and_putspaces(char *to, char *from, char c, int j);
char		*ft_jump_char(char *str, char c);
int			ft_cpy_pipe_and_putspaces(char *to, char *from, int j);
int			ft_is_rd(char *str, char c);
int			ft_is_two_rdout(char *str);

/* utils4.c */
char		*ft_put_pid(void);
char		*ft_group_array(char **args, int i);
t_args		*get_that_saved(t_args *args);
int			ft_good_if(char *line);

/* utils5.c */
char		**ft_add_to_array(char **array, char *new_line);
char		*ft_ignore_while_not(char *str, char c);
int			ft_is_alpha_blank_quote_s(char c);
int			ft_is_alpha_blank_dollar_quote_s(char c);
int			ft_is_pipe(char *str);

/* utils6.c */
void		ft_special_strlcpy(char **to, char *from, int *str_i, int size);
int			string_counter(char *str);
void		ft_strlcpy_w_quotes_helper(char *to, char *from, int *i, int *j);
void		ft_strlcpy_w_quotes(char **to, char *from, int *str_i, int size);
int			ft_isvalid_export(char *line, int i);

/* helper_functions.c */
char		**remove_from_line(char **env, char *line);
bool		is_there_line(char **env, char *line);
char		**add_line(char **env, char *line, int exp);
int			is_there_equal(char *line);

/* helper_function2.c */
void		free_array(char **array);
void		close_all_fds(void);
int			here_doc(t_args *args, t_command *cmd, t_pipes *pipes,
				char *limiter);
void		change_flag(t_command **cmd);

/* execution.c */
void		execution(t_command *cmd, char **envp, t_args *args);
void		built_in_execution(t_args *args, t_command *cmd,
				t_code built_in);

/* change.c */
void		change_in(t_command *cmd, int new_fd);
void		change_out(t_command *cmd, int new_fd);
void		change_next_in(t_command *cmd, int new_fd);
void		ft_goodfree_array(char ***array);
char		**init_envp(char **envp);
char		**env_creator(void);
void		ft_start_args(t_args *args);
void		good_close(t_command *cmd);

/* built_helper */
int			can_i_exit(char	*str);

/* helper_functions3.c */
int			spaces_handler(char **line);
void		free_children(t_args *args, t_command *cmd);
void		exec_caller(t_args *args, t_command *cmd, t_code built_in);

#endif
