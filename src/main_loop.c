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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nodes.h"
#include "env.h"

#include "ts_readline.h"

#ifndef PROMPT
# define PROMPT "\x1b[1;35m\x1b[?2004ltrain> \x1b[0m"
#endif

char	*aliasing(char *line, t_kv_list *aliases);
void	build_prompt(char *prompt, char *format, t_env *env);
void	free_node_array(t_node **nodes);
char	*get_ps1(t_kv_list *env);
t_node	**parse_line(char *line);
int		exec(t_node **nodes, t_env *env);
void	print_nodes(t_node **array);

int	main_loop(t_env *env) {
	t_node		**nodes;
	//char		prompt[256];
	char		*line;

	env->history = ts_init_hist();
	while (!env->should_exit) {
	//	build_prompt(prompt, get_ps1(env->env_list), env);
		line = ts_readline(PROMPT, env->history);
		if (!line)
			return (1);
		ts_add_hist(line, env->history);
		line = aliasing(line, env->aliases);
		if (!line)
			return (1);
		nodes = parse_line(line);
		free(line);
		if (!nodes)
			continue ;
//		print_nodes(nodes);
		exec(nodes, env);
		free_node_array(nodes);
	}
	ts_free_hist(env->history);
	return (0);
}
