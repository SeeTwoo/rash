/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_unalias.c                                        :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

#include "env.h"
#include "messages.h"
#include "nodes.h"

void	free_kv_list(t_key_value *list);
void	delete_kv_node(t_key_value **list, char *key);

static void	delete_all_aliases(t_env *env) {
	free_kv_list(env->aliases);
	env->aliases = NULL;
}

int	tshoo_unalias(t_node *node, t_env *env) {
	if (!(node->command[1]))
		return (dprintf(2, "%s%s\n", WARN_HD, UNAL_USAGE), 0);
	if (strncmp(node->command[1], "-a", 2) == 0)
		return (delete_all_aliases(env), 0);
	for (int i = 1; node->command[i]; i++)
		delete_kv_node(&env->aliases, node->command[i]);
	return (1);
}
