/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   kv_list.c                                           :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "kv_list.h"

t_kv_list	*new_kv_node(char *new_kv) {
	t_kv_list	*new = malloc(sizeof(t_kv_list));;
	size_t		len;

	if (!new)
		return (NULL);
	len = strcspn(new_kv, "=");
	new->raw = strdup(new_kv);
	new->key = strndup(new_kv, len);
	new->value = strdup(&new_kv[len + 1]);
	if (!(new->raw) || !(new->key) || !(new->value))
		return (free(new->raw), free(new->key), free(new->value), free(new), NULL);
	new->next = NULL;
	return (new);
}

void	add_kv_back(t_kv_list **list, t_kv_list *new) {
	t_kv_list	*temp;

	if (!(*list)) {
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	set_kv_value(t_kv_list *node, char *new, size_t name_len) {
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

t_kv_list	*kv_n_chr(t_kv_list *list, char *key, size_t n) {
	while (list) {
		if (strncmp(list->key, key, n) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	modify_kv_list(t_kv_list *kv, char *new, ssize_t key_len) {
	t_kv_list	*to_modify;

	to_modify = kv_n_chr(kv, new, key_len);
	if (to_modify)
		set_kv_value(to_modify, new, key_len);
	else
		add_kv_back(&kv, new_kv_node(new));
}

char	*get_kv_value(t_kv_list *list, char *key) {
	while (list) {
		if (strcmp(list->key, key) == 0)
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

char	*get_kv_n_value(t_kv_list *list, char *key, size_t n) {
	while (list) {
		if (strncmp(list->key, key, n) == 0)
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

t_kv_list	*kv_chr(t_kv_list *list, char *key) {
	while (list) {
		if (strcmp(list->key, key) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
