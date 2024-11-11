#ifndef BUILTIN_H
#define BUILTIN_H
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h>
// <<<<<<< HEAD
// #include"./libft/libft.h"
// =======
// #include"../../newpars/libft/libft.h"
// >>>>>>> ae8c0bf (merge conf)

// #define HERE_DOC 1
// #define WORD 2
// typedef struct s_env {
//     char *key;  
//    char *value;  

//     struct s_env *next;   
// } t_env;

typedef enum e_token_type {
    WORD, //0
    S_QUOTE, //1
    D_QUOTE, //2
    SPACES, //3
    ENV, //4
    PIPE, //5
    RED_IN, //6
    RED_OUT, //7
    RED_APP, //8
    HERE_DOC //9
} t_token_type;


typedef struct s_token{
    char *value;
    t_token_type type;
    struct s_token *next;

} t_token;
typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}	t_list;
typedef struct s_env {
	char			*key;
	char			*value;
	int				dx;
	struct s_env	*next;
}	t_env;




typedef struct s_red{
    char *value;
    t_token_type type;
    struct s_red *next;
    
} t_red;

typedef struct s_cmd{
    char **args;
    char *path;
    t_red *red;
    t_red *red_out;
    struct s_cmd *next;
} t_cmd;

// exec
typedef struct ex_er
{
	int	ex;
	int	er;
}	t_exer;
t_exer g_glb;
typedef struct t_extra
{
	int		i;
	int		size;
	int		*pid;
	int		**tube;
	char	**path;
	char	**envp;
}	t_extra;

// int	cd_var(char *var, t_env **env);
// void	ft_echo(char **arg);
// t_env ft_env(char **env, char **arg);
// void	ft_exit(char **cmd);
// t_env	ft_export(char **argv, char **env);
// void	ft_pwd(t_env *env);
// void	ft_unset(t_env **env, t_cmd *cmd);
// static void	process_heredocs(t_cmd *cmd, t_env *env);
//handle_child.............................................
void	handle_child(t_cmd	*cmd, t_env **env, t_extra ptr);
void	input_cmd(t_red *in, t_extra ptr, char **cmd);
void	output_cmd(t_red *out, t_extra ptr);
void	assaining_in(t_red *tmp);
int	assining_out(t_red *tmp, int	*fd);
void	condition_dup(t_extra ptr);
int	closingB(int **tube, int pos);
void	handle_exec(char **path, t_cmd	*list, t_env **env, char **envp);
// ...................................................
//allocptr.............................................
void	allocptr(t_extra *ptr, t_env **tmp, t_env **env);
char	**env_to_envp(t_env **env);
t_env	*getEnvarement(t_env **env, char *key);
void	Tslash(char **path);
int	size_env(t_env	**env);
// ...................................................
//main.............................................
t_env	*get_env(char **env);
void	check_Opwd(char **str);
int	**prc_allocation(int size);
void	execution(t_cmd **list, t_env **env);
// ...................................................

//cleaning.............................................
void	free_tab(char **tab);
void	ft_free_wait(t_extra ptr);
// ...................................................
// libft.............................................
int	ft_strcmp(const char *s1, char *s2);
size_t	ft_strlen(const char *s);
static int	nbrarray(char const *s, char c) ;
void	frealltab(char **str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
static int	checkimpli(char const *s, char **str, char c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_size_list(t_cmd *list);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front_env(t_env **lst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *key, char *value);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s);
char	**ft_strplit(char *env);
// ...................................................

#endif