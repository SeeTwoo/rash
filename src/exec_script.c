/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   exec_script.c                                       :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "nodes.h"
#include "env.h"

char	*aliasing(char *line, t_kv_list *aliases);
int		exec(t_node **nodes, t_env *env);
void	free_node_array(t_node **nodes);
char	*get_next_line(int fd);
t_node	**parse_line(char *line);

void	nullifythenewline(char *line) {
	char	*nl;

	nl = strrchr(line, '\n');
	if (!nl)
		return ;
	*nl = '\0';
}

void	exec_script(t_env *env, char *path) {
	t_node	**nodes;
	char	*line;
	int		fd = open(path, O_RDONLY);

	if (fd == -1)
		return ;
	while (1) {
		line = get_next_line(fd);
		if (!line || line[0] == '\0')
			return ;
		nullifythenewline(line);
		line = aliasing(line, env->aliases);
		if (!line)
			return ;
		nodes = parse_line(line);
		free(line);
		if (!nodes)
			continue ;
		exec(nodes, env);
		free_node_array(nodes);
	}
	close(fd);
}
