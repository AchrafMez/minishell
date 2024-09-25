#include <stdio.h>
#include <unistd.h>


int	main(void)
{
	char *pwd = getcwd(NULL, 0);
	while (*pwd)
	{
		write(1, pwd, 1);
		pwd++;
	}
	write(1, "\n", 1);
	return (0);
}