#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "nodes.h"

char	**first_arg(char **command) {
	if (command[1] && strncmp(command[1], "-n", 2) == 0)
		return (&command[2]);
	return (&command[1]);
}

int	tshoo_echo(t_node *command, t_env *env) {
	char	**args;

	(void)env;
	args = first_arg(command->command);
	while (*args) {
		write(1, *args, strlen(*args));
		if (args[1])
			write(1, " ", 1);
		args++;
	}
	if (command->command[1] && strncmp(command->command[1], "-n", 2) == 0)
		return (0);
	write(1, "\n", 1);
	return (0);
}
