/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_exit.c                                           :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "env.h"
#include "nodes.h"

void	free_node_array(t_node **nodes);
void	free_double_array(char **array);

int	ts_exit(t_node *node, t_node **nodes, t_env *env) {
	(void)node;
	free_node_array(nodes);
	free_double_array(env->paths);
	exit(EXIT_SUCCESS);
}
