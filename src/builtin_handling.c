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

int	expand_command(char **cmd, t_key_value *env);
int	setup_redirections(t_node *node);
int	trim_command(t_node *node);
int	ts_alias(t_node *cmd, t_env *env);
int	ts_cd(t_node *cmd, t_env *env);
int	ts_env(t_node *cmd, t_env *env);
int	ts_exit(t_node *cmd, t_env *env);
int	ts_echo(t_node *cmd, t_env *env);
int	ts_unalias(t_node *cmd, t_env *env);
int	ts_unset(t_node *cmd, t_env *env);

typedef int	(*t_builtin)(t_node *cmd, t_env *env);

t_builtin	is_builtin(char *name) {
	if (!name)
		return (NULL);
	if (strcmp(name, "exit") == 0)
		return (ts_exit);
	else if (strcmp(name, "echo") == 0)
		return (ts_echo);
	else if (strcmp(name, "cd") == 0)
		return (ts_cd);
	else if (strcmp(name, "alias") == 0)
		return (ts_alias);
	else if (strcmp(name, "unalias") == 0)
		return (ts_unalias);
	else if (strcmp(name, "env") == 0)
		return (ts_env);
	else if (strcmp(name, "unset") == 0)
		return (ts_unset);
	return (NULL);
}

void	exec_builtin(t_builtin func, t_node *node, t_env *env) {
	int	saved_stdin = dup(STDIN_FILENO);
	int	saved_stdout = dup(STDOUT_FILENO);

	expand_command(node->command, env->env_list);
	trim_command(node);
	setup_redirections(node);
	func(node, env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
