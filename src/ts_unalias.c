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

void	free_kv_list(t_kv_list *list);
void	free_kv_node(t_kv_list *node);

static void	delete_all_aliases(t_env *env) {
	free_kv_list(env->aliases);
	env->aliases = NULL;
}

static void	delete_alias(t_env *env, char *key) {
	t_kv_list	*prev;
	t_kv_list	*temp;
	t_kv_list	*to_delete;

	prev = NULL;
	temp = env->aliases;
	to_delete = NULL;
	while (temp) {
		if (strcmp(temp->key, key) == 0) {
			to_delete = temp;
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
	if (!to_delete)
		return ;
	if (prev == NULL)
		env->aliases = to_delete->next;
	else
		prev->next = to_delete->next;
	free_kv_node(to_delete);
	return ;
}

int	ts_unalias(t_node *node, t_env *env) {
	if (!(node->command[1]))
		return (dprintf(2, "%s%s\n", WARN_HD, UNAL_USAGE), 0);
	if (strncmp(node->command[1], "-a", 2) == 0)
		return (delete_all_aliases(env), 0);
	for (int i = 1; node->command[i]; i++)
		delete_alias(env, node->command[i]);
	return (1);
}
