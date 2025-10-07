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

static void	set_value(t_kv_list *node, char *new_kv) {
	char	*value_start;

	value_start = strchr(new_kv, '=') + 1;
	free(node->raw);
	free(node->value);
	node->raw = strdup(new_kv);
	node->value = strdup(value_start);
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

static void	insert_alias(t_env *env, t_kv_list *new) {
	t_kv_list	*temp;

	if (!new)
		return ;
	if (!(env->aliases)) {
		env->aliases = new;
		return ;
	}
	temp = env->aliases;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

static t_kv_list	*new_kv_node(char *new_kv) {
	t_kv_list	*new;
	size_t		len;

	new = malloc(sizeof(t_kv_list));
	if (!new)
		return (NULL);
	len = strcspn(new_kv, "=");
	new->raw = strdup(new_kv);
	new->key = strndup(new_kv, len);
	new->value = strdup(&new_kv[len + 1]);
	new->next = NULL;
	return (new);
}

void	add_alias(t_env *env, char *arg) {
	t_kv_list	*temp;

	temp = env->aliases;
	while (temp) {
		if (strncmp(temp->key, arg, strlen(temp->key)) == 0) {
			set_value(temp, arg);
			return ;
		}
		temp = temp->next;
	}
	insert_alias(env, new_kv_node(arg));
}

int	ts_alias(t_node *node, t_env *env) {
	if (!node->command[1])
		return (display_aliases(env->aliases), 0);
	for (int i = 1; node->command[i]; i++)
		if (is_valid_alias(node->command[i]))
			add_alias(env, node->command[i]);
	return (0);
}
