
#include "builtin.h"

// Function to check if the argument is "-n"
int	all_n(char	*tab)
{
	if (*tab != '-') // Check if it starts with '-'
		return (0);
	tab++; // Move to the next character
	while (*tab) // Check all following characters
	{
		if (*tab != 'n') // If not 'n', return false
			return (0);
		tab++; // Move to the next character
	}
	return (1); // All characters are 'n'
}

// Function to print the arguments
void	print_arguments(char **arg)
{
	int	i = 0; // Index for arguments

	while (arg[i])
	{
		if (arg[i + 1]) // If not the last argument
			printf("%s ", arg[i]); // Print with a space
			p
		else
			printf("%s", arg[i]); // Print the last argument without a space
		i++; // Move to the next argument
	}
}

// Echo function implementation
void	ft_echo(char **arg, int fd)
{
	int	i = 1; // Start from the first argument
	int	no_line = 0; // Flag for new line

	
	if (!arg[1]) // If no arguments, print newline
	{
		printf("\n");
		return;
	}

	// Check if the first argument is "-n"
	if (all_n(arg[1]))
		no_line = 1; // Set flag if it is
	if (no_line)
		i++; // Skip the "-n" argument

	print_arguments(&arg[i]); // Print the remaining arguments
	if (!no_line) // If not using -n
		printf("\n"); // Print a newline at the end
}