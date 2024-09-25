#ifndef BUILTING_H
# define BUILTING_H
#include"./libft/libft.h"
typedef struct my_env
{
	char *name;
	char *value;
	struct my_env *next;
} t_env;

typedef struct my_builtin
{
	t_env *env_list;
} t_builtin;

#endif