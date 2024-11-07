
#include "builtin.h"
void	remove_env_var(t_env **env, t_cmd *cmd, int i)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, cmd->args[i],
				ft_strlen(cmd->args[i])) == 0
			&& ft_strlen(cmd->args[i]) == ft_strlen(tmp->key))
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_env **env, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i] != NULL)
	{
		remove_env_var(env, cmd, i);
		i++;
	}
}