/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   builtin_handling.c                                  :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

#include "env.h"
#include "nodes.h"

int	setup_redirections(t_node *node);
int	ts_cd(t_node *node);
int	ts_exit(t_node *node, t_node **nodes, t_env *env);
int	ts_echo(t_node *command);

int	is_builtin(char *name) {
	if (strcmp(name, "exit") == 0)
		return (1);
	else if (strcmp(name, "echo") == 0)
		return (1);
	else if (strcmp(name, "cd") == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_node *node, t_node **nodes, t_env *env) {
	int	saved_stdin = dup(STDIN_FILENO);
	int	saved_stdout = dup(STDOUT_FILENO);

	setup_redirections(node);
	if (strcmp(node->command[0], "exit") == 0)
		ts_exit(node, nodes, env);
	else if (strcmp(node->command[0], "echo") == 0)
		ts_echo(node);
	else if (strcmp(node->command[0], "cd") == 0)
		ts_cd(node);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
