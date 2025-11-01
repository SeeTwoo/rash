#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nodes.h"
#include "env.h"

#include "tshoo_line.h"

#ifndef PROMPT
# define PROMPT "\x1b[1;32m\x1b[?2004ltrain> \x1b[0m"
#endif

char	*aliasing(char *line, t_key_value *aliases);
void	build_prompt(char *prompt, char *format, t_env *env);
int		exec(t_node **nodes, t_env *env);
void	free_node_array(t_node **nodes);
char	*get_next_line(int fd);
t_node	**parse_line(char *line);
void	print_nodes(t_node **array);
/*
static int	contains_unclosed_quotes(char *line) {
	char	quote = 0;

	while (*line) {
		if (*line == '\'' || *line == '"') {
			if (quote == 0)
				quote = *line;
			else if (quote == *line)
				quote = 0;
		}
		line++;
	}
	return (quote != 0);
}
*/

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
	nodes = parse_line(line);
	if (!nodes)
		return (1);
//	print_nodes(nodes);
	exec(nodes, env);
	free_node_array(nodes);
	return (0);
}

char	*get_script_line(int fd, t_env *env) {
	char	*line = get_next_line(fd);

	if (!line)
		return NULL;
	nullifythenewline(line);
	return (aliasing(line, env->aliases));
}

int	script_loop(t_env *env, char *path) {
	char	*line;
	int		fd = open(path, O_RDONLY);

	if (fd == -1)
		return (1);
	while (1) {
		line = get_script_line(fd, env);
		if (!line)
			return (close(fd), 1);
		process_line(line, env);
		free(line);
	}
	close(fd);
	return (0);
}

char	*get_interactive_line(char *prompt, t_env *env) {
	char	*line = tshoo_line(prompt, env->history);

	if (!line)
		return NULL;
	tshoo_add_hist(line, env->history);
	return (aliasing(line, env->aliases));
}

int	interactive_loop(t_env *env) {
	char		prompt[256];
	char		*line;

	env->history = tshoo_init_hist();
	while (!env->should_exit) {
		build_prompt(prompt, get_kv_value(env->env_list, "PS1"), env);
		line = get_interactive_line(prompt, env);
		if (!line)
			continue ;
		process_line(line, env);
		free(line);
	}
	tshoo_free_hist(env->history);
	return (0);
}
