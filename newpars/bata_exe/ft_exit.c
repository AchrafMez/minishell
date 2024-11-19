#include "../minishell.h"


int	is_nb(char *tab)
{
	int	i;

	i = 0;
	if (tab[i] == '-' || tab[i] == '+')
		i++;
	while (tab[i] >= '0' && tab[i] <= '9')
		i++;
	if (!tab[i])
		return (1);
	return (0);
}

void	ft_exit(char **cmd)
{
	printf("exit\n");
	if (!cmd[1])
		exit(0);
	if (is_nb(cmd[1]))
	{
		if (!cmd[2])
			exit(ft_atoi(cmd[1]));
		else
		{
			write(2, "exit : too many arguments\n", 26);
			g_glb.ex = 1;
		}
	}
	else
	{
		write(2, "exit : numeric argument required\n", 33);
		exit(255);
	}
}
