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

char	*ts_readline(char *prompt);

#ifndef PROMPT
# define PROMPT "\x1b[1;36m\x1b[?2004ltrain> \x1b[0m"
#endif

char	*aliasing(char *line, t_kv_list *aliases);
void	free_node_array(t_node **nodes);
t_node	**parse_line(char *line);
int		exec(t_node **nodes, t_env *env);
void	print_nodes(t_node **array);

int	main_loop(t_env *env) {
	t_node	**nodes;
	char	*line;

	while (!env->should_exit) {
		line = ts_readline(PROMPT);
		if (!line)
			return (1);
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
	return (0);
}
