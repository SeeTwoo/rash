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
int	trim_command(t_node *node);
int	ts_alias(t_node *node, t_env *env);
int	ts_cd(t_node *node, t_kv_list *env);
int	ts_env(t_kv_list *list);
int	ts_exit(t_env *env);
int	ts_echo(t_node *command);
int	ts_unalias(t_node *node, t_env *env);

int	is_builtin(char *name) {
	if (!name)
		return (0);
	if (strcmp(name, "exit") == 0)
		return (1);
	else if (strcmp(name, "echo") == 0)
		return (1);
	else if (strcmp(name, "cd") == 0)
		return (1);
	else if (strcmp(name, "alias") == 0)
		return (1);
	else if (strcmp(name, "unalias") == 0)
		return (1);
	else if (strcmp(name, "env") == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_node *node, t_env *env) {
	int	saved_stdin = dup(STDIN_FILENO);
	int	saved_stdout = dup(STDOUT_FILENO);

	trim_command(node);
	setup_redirections(node);
	if (strcmp(node->command[0], "exit") == 0)
		ts_exit(env);
	else if (strcmp(node->command[0], "echo") == 0)
		ts_echo(node);
	else if (strcmp(node->command[0], "cd") == 0)
		ts_cd(node, env->env_list);
	else if (strcmp(node->command[0], "alias") == 0)
		ts_alias(node, env);
	else if (strcmp(node->command[0], "unalias") == 0)
		ts_unalias(node, env);
	else if (strcmp(node->command[0], "env") == 0)
		ts_env(env->env_list);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
