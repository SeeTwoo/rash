/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   exec.c                                              :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "env.h"
#include "messages.h"
#include "nodes.h"

void	assign_variable(t_env *env, char *new);
void	close_every_fd(void);
void	exec_builtin(t_node *node, t_env *env);
void	free_double_array(char **array);
void	free_kv_list(t_kv_list*);
void	free_node_array(t_node **nodes);
int		get_command_binary_path(t_node *node, char **paths);
int		is_builtin(char *name);
void	print_nodes(t_node **nodes);
int		setup_redirections(t_node *command);
int		trim_command(t_node *node);

//protection of the pipe creation
static int	get_pipes(t_node **nodes, int command_number) {
	int	pipe_number;
	int	temp[2];

	pipe_number = command_number - 1;
	nodes[0]->in = STDIN_FILENO;
	nodes[pipe_number]->out = STDOUT_FILENO;
	for (int i = 0; i < pipe_number; i++) {
		pipe(temp);
		nodes[i]->out = temp[1];
		nodes[i + 1]->in = temp[0];
	}
	return (0);
}

static void	clean_child_process(t_node **nodes, t_env *env) {
	free_node_array(nodes);
	free_double_array(env->paths);
	ts_free_hist(env->history);
	free_kv_list(env->aliases);
	close_every_fd();
}

static void	error_child_process(t_node **nodes, t_env *env) {
	clean_child_process(nodes, env);
	exit(EXIT_FAILURE);
}

static void	exec_command(t_node *command, t_env *env, t_node **nodes) {
	char	**cmd_args;

	command->pid = fork();
	if (command->pid != 0)
		return ;
	trim_command(command);
	if (setup_redirections(command) == 1)
		error_child_process(nodes, env);
	cmd_args = command->command;
	command->command = NULL;
	clean_child_process(nodes, env);
	execve(cmd_args[0], cmd_args, env->env);
	free_double_array(cmd_args);
	exit(EXIT_FAILURE);
}

int	exec(t_node **nodes, t_env *env) {
	int		command_number;
	
	command_number = 0;
	while (nodes[command_number])
		command_number++;
	get_pipes(nodes, command_number);
	for (int i = 0; i < command_number; i++) {
		if (is_builtin(nodes[i]->command[0]))
			exec_builtin(nodes[i], env);
		else if (get_command_binary_path(nodes[i], env->paths) == 0)
			exec_command(nodes[i], env, nodes);
		else if (strchr(nodes[i]->command[0], '='))
			assign_variable(env, nodes[i]->command[0]);
		else
			dprintf(2, "%s%s : %s\n", ERR_HD, nodes[i]->command[0], CMD_FND);
	}
	close_every_fd();
	while (--command_number >= 0)
		waitpid(nodes[command_number]->pid, 0, 0);
	return (0);
}
