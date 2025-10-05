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

static void	add_alias(t_env *env, t_kv_list *alias) {
	t_kv_list	*temp;

	if (!env->aliases) {
		env->aliases = alias;
		return ;
	}
	temp = env->aliases;
	while (temp->next)
		temp = temp->next;
	temp->next = alias;
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

int	ts_alias(t_node *node, t_env *env) {
	t_kv_list	*current;

	if (!node->command[1])
		return (display_aliases(env->aliases), 1);
	if (!strchr(node->command[1], '='))
		return (1);
	current = env->aliases;
	while (current) {
		if (strcmp(node->command[1], current->key) == '=') {
			set_value(current, node->command[1]);
			return (0);
		}
		current = current->next;
	}
	add_alias(env, new_kv_node(node->command[1]));
	//current = new_kv_node(node->command[1]);
	return (0);
}
