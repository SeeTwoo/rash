/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   main_loop.c                                         :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nodes.h"
#include "env.h"

#include "ts_readline.h"

#ifndef PROMPT
# define PROMPT "\x1b[1;32m\x1b[?2004ltrain> \x1b[0m"
#endif

char	*aliasing(char *line, t_kv_list *aliases);
void	build_prompt(char *prompt, char *format, t_env *env);
int		exec(t_node **nodes, t_env *env);
void	free_node_array(t_node **nodes);
char	*get_kv_value(t_kv_list *list, char *key);
char	*get_next_line(int fd);
t_node	**parse_line(char *line);
void	print_nodes(t_node **array);
char	*trim_string(char *s);

void	nullifythenewline(char *line) {
	char	*nl;

	nl = strrchr(line, '\n');
	if (!nl)
		return ;
	*nl = '\0';
}

int	process_line(char *line, t_env *env) {
	t_node		**nodes;

	if (line[0] == '#')
		return (0);
	line = aliasing(line, env->aliases);
	nodes = parse_line(line);
	if (!nodes)
		return (1);
//	print_nodes(nodes);
	exec(nodes, env);
	free_node_array(nodes);
	free(line);
	return (0);
}

int	script_loop(t_env *env, char *path) {
	char	*line;
	int		fd = open(path, O_RDONLY);

	if (fd == -1)
		return (1);
	while (1) {
		line = get_next_line(fd);
		if (!line)
			return (1);
		nullifythenewline(line);
		process_line(line, env);
	}
	close(fd);
	return (0);
}

int	interactive_loop(t_env *env) {
	char		prompt[256];
	char		*line;

	env->history = ts_init_hist();
	while (!env->should_exit) {
		build_prompt(prompt, get_kv_value(env->env_list, "PS1"), env);
		line = ts_readline(prompt, env->history);
		if (!line)
			return (1);
		ts_add_hist(line, env->history);
		process_line(line, env);
	}
	ts_free_hist(env->history);
	return (0);
}
