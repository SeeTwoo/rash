/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   assign_variable.c                                   :+:     :+:    :+:   */
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
#include "messages.h"

void	add_env_variable(t_kv_list **head, char *s);

t_kv_list	*lstchr(t_kv_list *head, char *s, size_t len) {
	while (head) {
		if (strncmp(head->key, s, len) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

int	set_env_node(t_kv_list *node, char *new, size_t name_len) {
	char	*new_raw = strdup(new);
	char	*new_value = strdup(&new[name_len + 1]);

	if (!new_raw || !new_value)
		return (free(new_raw), free(new_value), 1);
	free(node->raw);
	free(node->value);
	node->raw = new_raw;
	node->value = new_value;
	return (0);
}

void	assign_variable(t_env *env, char *new) {
	t_kv_list	*node;
	size_t		name_len = strcspn(new, "=");

	if (name_len == 0) {
		dprintf(2, "%s%s\n", WARN_HD, NEED_NAME);
		return ;
	}
	node = lstchr(env->env_list, new, name_len);
	if (node)
		set_env_node(node, new, name_len);
	else
		add_env_variable(&(env->env_list), new);
}
