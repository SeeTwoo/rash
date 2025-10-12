/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_alias.c                                          :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "env.h"
#include "kv_list.h"
#include "messages.h"
#include "nodes.h"

void	modify_kv_list(t_kv_list *kv, char *new, ssize_t key_len);

static void	display_aliases(t_kv_list *aliases) {
	while (aliases) {
		printf("%s\n", aliases->raw);
		aliases = aliases->next;
	}
}

static ssize_t	is_valid_alias(char *new_kv) {
	ssize_t	key_len;

	if (!strchr(new_kv, '='))
		return (dprintf(2, "%s%s\n", WARN_HD, NEED_EQUAL), -1);
	key_len = strcspn(new_kv, "=");
	if (key_len == 0)
		return (dprintf(2, "%s%s\n", WARN_HD, NEED_PATTERN), -1);
	return (key_len);
}

int	ts_alias(t_node *node, t_env *env) {
	ssize_t	key_len;

	if (!node->command[1])
		return (display_aliases(env->aliases), 0);
	for (int i = 1; node->command[i]; i++) {
		key_len = is_valid_alias(node->command[i]);
		if (key_len == 1)
			continue ;
		modify_kv_list(env->aliases, node->command[i], key_len);
	}
	return (0);
}
