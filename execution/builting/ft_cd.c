
#include "builtin.h"

t_env	*get_env_node(t_env **env, char *key)
{
	t_env	*tmp = *env; 

	while (tmp)
	{
		if (strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
void	change_pwd_oldpwd(t_env **env)
{
	t_env	*tmp = get_env_node(env, "PWD"); 
	t_env	*tmp2 = get_env_node(env, "OLDPWD"); 
	char	*ret; 

	if (!tmp || !tmp2) 
		return;

	if (tmp2->value) 
		free(tmp2->value);
	tmp2->value = ft_strdup(tmp->value); 

	ret = getcwd(NULL, 0); 
	if (ret)
	{
	
		free(tmp->value);
		tmp->value = ret; 
	}
	else
	{

		printf("cd: error retrieving current directory:\ngetcwd: cannot access parent directories: No such file or directory\n");
	}
}


int	cd_var(char *var, t_env **env)
{
	t_env	*tmp = get_env_node(env, var); 

	if (!tmp || !*tmp->value) 
	{
		
		write(2, "cd: ", 4);
		write(2, var, ft_strlen(var)); 
		write(2, " not set\n", 9); 
		return (0);
	}

	if (chdir(tmp->value) == -1) 
	{

		perror("cd"); 
		return (0);
	}

	if (strcmp(var, "OLDPWD")) 
		printf("%s\n", tmp->value);
	
	return (1);
}

// Main cd function
void	ft_cd(t_env **env, char **arg)
{
	
	if (arg[1] == NULL || strcmp(arg[1], "~"))
	{
		if (!cd_var("HOME", env)) 
			return;
	}
	else if (strcmp(arg[1], "-")) 
	{
		if (!cd_var("OLDPWD", env)) 
			return;
	}
	else
	{
		if (chdir(arg[1]) == -1) 
		{
			perror("cd"); 
			return;
		}
	}
	change_pwd_oldpwd(env); 
}