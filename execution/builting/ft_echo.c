#include <string.h>
#include <unistd.h>


int	check_n(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[], char **env)
{
	// i did this flag to check if the -n flag is set
	int print_newline = 1;

	// check if the first argument is -n
	if (argc > 1 && check_n(argv[1]) == 1)
	{
		print_newline = 0;
		int i = 1;
		while (i < argc - 1)
		{
			argv[i] = argv[i + 1];
			i++;
		}
		argc--;
	}

	// so i print each arguments in the terminal
	int i = 1;
	while (i < argc)
	{
		size_t len = strlen(argv[i]);
		write(1, argv[i], len);
		if (i < argc - 1)
		{
			write(1, " ", 1);
		}
		i++;
	}

	if (print_newline)
	{
		write(1, "\n", 1);
	}

	return (0);
}
	