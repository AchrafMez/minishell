/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 04:35:32 by amezioun          #+#    #+#             */
/*   Updated: 2024/12/05 07:31:27 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include "./libft/libft.h"
# include <stdio.h>
// # include "/Users/amezioun/.brew/opt/readline/include/readline/history.h"
// # include "/Users/amezioun/.brew/opt/readline/include/readline/readline.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
#define COLOR "\033[1;36m"
#define COLOR_RESET "\033[0m"

char					*get_next_line(int fd);

typedef enum e_token_type
{
	WORD,
	S_QUOTE,
	D_QUOTE,
	SPACES,
	ENV,
	PIPE,
	RED_IN,
	RED_OUT,
	RED_APP,
	HERE_DOC,
	EXIT_STATUE
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;

}						t_token;

// //for the environment
typedef struct s_env
{
	char				*key;
	char				*value;
	int					dx;
	struct s_env		*next;
}						t_env;

typedef struct s_red
{
	char				*value;
	int					fd_in;
	t_token_type		type;
	struct s_red		*next;

}						t_red;

typedef struct s_command
{
	char				*name;
	char				**args;
	char				*path;
	t_red				*in;
	t_red				*out;
	int					fd;
	struct s_command	*next;
}						t_command;

typedef struct s_content
{
	char				**cur;
	char				*buffer;
	int					*buf_idx;
	t_token				**token_list;
	t_env				*env;
}						t_content;

//-----------------------------exec-----------------------------//
void					exec_built(t_command *cmd, t_env **env);
int						is_built_in(t_command *command);
// built_in
int						cd(char **args, t_env *env);
int						pwd(t_env **env);
// export
int						is_valid_key(char *arg);
void					print_export(t_env *env);
t_env					*find(t_env *env, char *key);
void					set_export_env(t_env **env, char *key, char *value);
int						ft_export(char **args, t_env **env);
// unset
int						unset(char **args, t_env **env);
int						ft_exit(char **args, int last_e_s);

// token_utils
t_token					*create_token(char *value, t_token_type type);
t_token					*ret_last_token(t_token **token_list);
void					add_token(t_token **token_list, t_token *new_token);
void					print_tokens(t_token *token_list);
void					ft_tokens_free(t_token *token_list);
void					tokens_edit(t_token **token_list);
void					delete_space(t_token **token_list);

//----------------------------tokenizer-----------------//
// quotes
void					read_and_tokenize(t_env **env, t_token **token_list);
int						check_single(char **cur, char *buffer, int *buf_idx);
void					check_single_for_helper(t_content *content);
int						handle_singlequote_helper(t_content *content);
int						handle_single_quote(t_content *content);

void					handle_double_quote_helper(t_content *content);
int						handle_double_quote(t_content *content);

void					handle_dollar_helper(t_content *content, char *expanded,
							int flag);
void					handle_dollar(t_content *content, int flag);
int						handle_quotes(t_content *content);
void					handle_space(char **cur, char *buffer, int *buf_idx,
							t_token **token_list);
int						handle_pipe(char **cur, char *buffer, int *buf_idx,
							t_token **token_list);
int						handle_red_in(char **cur, char *buffer, int *buf_idx,
							t_token **token_list);
int						handle_red_out(char **cur, char *buffer, int *buf_idx,
							t_token **token_list);
int						handle_red(t_content *content);
t_token					*tokenize_input(char *input, t_env **env);

//----------------------------env-----------------------/
// env
void					dup_env(char **envp, t_env **env);
void					display_env(t_env *tmp);
void					ft_free_env(t_env **env);

t_env					*convert_env(char **env);

// expanding tools
char					*get_env_value(t_env *env, char *searsh);
void					set_env_value(t_env **env, char *searsh, char *set);
void					update_exit_value(t_env **env, int status);

//---------------------------parser--------------------//
int						check_syntax(t_token *token);
int						check_unclosed_quotes(char *input);
// cmd utils
t_command				*create_command(void);
void					add_arg(char ***args, int *arg_count, char *value);
void					add_red(t_red **red_list, char *value,
							t_token_type type);
void					free_cmd(t_command *command);
void					print_cmd(t_command *command);

void					print_command(t_command *command);
t_command				*fill_cmd_assit1(t_command **cmd_list);
void					fill_cmd_assit(t_token *token, t_command *cmd,
							int *arg_count, t_env *env);
t_command				*fill_command(t_token *tokens, t_env *env);

// path
void					set_path(t_command **cmd);
char					*get_path(char *target);
void					free_path(char **path);
char					*join_path(char *dir, char *target);
int						check_access(char *full_path);
char					**get_env_path(void);
char					*find_exec(char **path, char *target);

void					main_loop(t_env **env);

// //signal
void					ctrl_c(int sig);
void					ctrl_d(void);
void					handle_signals(void);

//----------------------------execution---------------------------------//
typedef struct t_extra
{
	int					i;
	int					size;
	int					*pid;
	int					**tube;
	char				**path;
	char				**envp;
	t_env				**env;
}						t_extra;

typedef struct s_list
{
	char				*content;
	int					type;
	struct s_list		*next;
}						t_list;

void					handle_child(t_command *cmd, t_env **env, t_extra ptr);
void					input_cmd(t_red *in, t_extra ptr, char **cmd, int fd);
void					output_cmd(t_red *out, t_extra ptr);
void					assaining_in(t_red *tmp, int fd, t_env **env);
int						ass_out(t_red *tmp, int *fd);
void					condition_dup(t_extra ptr);
int						closingb(int **tube, int pos);
void					handle_exec(char **path, t_command *list, t_env **env,
							char **envp);
int						there_is_slash(char *arg);
void					slash_exec(char **arg, char **envp, t_env **env);
void					execute_command(char **path, t_command *list,
							t_env **env, char **envp);

// ...................................................
void					allocptr(t_extra *ptr, t_env **tmp, t_env **env);
char					**env_to_envp(t_env **env);
t_env					*get_envarement(t_env **env, char *key);
t_env					*get_envarement(t_env **env, char *key); // 2

void					t_slash(char **path);
int						size_env(t_env **env);
// ...................................................
t_env					*get_env(char **env);
void					check_o_pwd(char **str); // 4
int						**prc_allocation(int size);
void					execution(t_command **list, t_env **env);
int						**builtins_tube(t_command **list, t_env **env,
							int size);
int						is_builting(t_command *cmd);
void					exec_builtins(t_command *cmd, t_env **env);
int						open_files(int *fd, t_command *cmd, t_env **env);
int						output_builtins(t_red *out);
int						input_builtins(t_red *in);
int						out_fd_assign(t_red *tmp, int *fd);
void					duplicate_fd(int *ret, int fd);
int						**alloc_tube(int size);
int						open_pipes(int **tube, int size);
int						execute_builtin_command(t_command *cmd, t_env **env);

// ...................................................
// builtins.............................................
int						ft_echo(char **arg);
int						cd_update_environment(t_env *env);

// ...................................................
// cleaning.............................................
void					free_tab(char **tab);
void					ft_free_wait(t_extra ptr, t_env **env);

// ...................................................
// libft.............................................
void					frealltab(char **str);
void					command_not_found(char **arg, char *str, int ex,
							t_env **env);
int						ft_size_list(t_command *list);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_front_env(t_env **lst, t_env *new);
t_env					*ft_lstlast_env(t_env *lst);
void					ft_lstadd_back_env(t_env **lst, t_env *new);
t_env					*ft_lstnew_env(char *key, char *value);
void					*ft_memcpy(void *dest, const void *src, size_t n);
char					**ft_strplit(char *env);
int						condition_name(char *c);
void					free_env(t_env *node);
void					env_del(t_env *lst);
char					*ft_strncpy(char *dest, char *src, unsigned int n);
int						ft_enva(t_env **env, char **arg);
// heredoc.............................................
void					get_herdoc(t_command **p_cmd, t_env *env);
int						handle_here_doc(char *limiter, t_env *env);
void					herdoc_sig(int sig);
int						help_heredoc(char *line, int i, int fd, t_env *env);
void					ft_dollar(char *str, int *i, int fd, t_env *env);
int						ft_chr(const char *s, int c);
int						ft_strncmpp(const char *s1, const char *s2, size_t n);
void					ft_error(char *message, int exit_code, int f);
// ...................................................

#endif