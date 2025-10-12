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

static void	display_aliases(t_kv_list *aliases) {
	while (aliases) {
		printf("%s\n", aliases->raw);
		aliases = aliases->next;
	}
}

static size_t	is_valid_alias(char *new_kv) {
	size_t	pattern_len;
	size_t	replace_len;

	if (!strchr(new_kv, '='))
		return (dprintf(2, "%s%s\n", WARN_HD, NEED_EQUAL), 0);
	pattern_len = strcspn(new_kv, "=");
	replace_len = strlen(&new_kv[pattern_len + 1]);
	if (pattern_len == 0)
		return (dprintf(2, "%s%s\n", WARN_HD, NEED_PATTERN), 0);
	if (replace_len == 0)
		return (dprintf(2, "%s%s\n", WARN_HD, NEED_REPLACE), 0);
	return (1);
}

void	add_alias(t_kv_list *aliases, char *arg) {
	t_kv_list	*to_modify;

	to_modify = kv_chr(aliases, arg);
	if (!to_modify) {
		add_kv_back(&aliases), arg);
		return ;
	}
	set_kv_value(to_modify, arg);
}

int	ts_alias(t_node *node, t_env *env) {
	if (!node->command[1])
		return (display_aliases(env->aliases), 0);
	for (int i = 1; node->command[i]; i++)
		if (is_valid_alias(node->command[i]))
			add_alias(env, node->command[i]);
	return (0);
}
