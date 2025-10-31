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

#include "key_value.h"

t_key_value	*new_kv_node(char *new_kv) {
	t_key_value	*new = malloc(sizeof(t_key_value));;
	size_t		len;

	if (!new)
		return (NULL);
	len = strcspn(new_kv, "=");
	new->key = strndup(new_kv, len);
	new->value = strdup(&new_kv[len + 1]);
	if (!(new->key) || !(new->value))
		return (free(new->key), free(new->value), free(new), NULL);
	new->next = NULL;
	return (new);
}

void	add_kv_back(t_key_value **list, t_key_value *new) {
	t_key_value	*temp;

	if (!(*list)) {
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	set_kv_value(t_key_value *node, char *new, size_t name_len) {
	char	*new_value = strdup(&new[name_len + 1]);

	if (!new_value)
		return (free(new_value), 1);
	free(node->value);
	node->value = new_value;
	return (0);
}

t_key_value	*kv_n_chr(t_key_value *list, char *key, size_t n) {
	char	*temp = strndup(key, n);

	if (!temp)
		return (NULL);
	while (list) {
		if (strcmp(temp, list->key) == 0)
			return (free(temp), list);
		list = list->next;
	}
	free(temp);
	return (NULL);
}

void	modify_kv_list(t_key_value **kv, char *new, ssize_t key_len) {
	t_key_value	*to_modify;

	to_modify = kv_n_chr(*kv, new, key_len);
	if (to_modify)
		set_kv_value(to_modify, new, key_len);
	else
		add_kv_back(kv, new_kv_node(new));
}

char	*get_kv_value(t_key_value *list, char *key) {
	while (list) {
		if (strcmp(list->key, key) == 0)
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

char	*get_kv_n_value(t_key_value *list, char *key, size_t n) {
	char	*temp = strndup(key, n);

	if (!temp)
		return (NULL);
	while (list) {
		if (strcmp(list->key, temp) == 0)
			return (free(temp), list->value);
		list = list->next;
	}
	free(temp);
	return (NULL);
}

t_key_value	*kv_chr(t_key_value *list, char *key) {
	while (list) {
		if (strcmp(list->key, key) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	free_kv_node(t_key_value *node) {
	free(node->key);
	free(node->value);
	free(node);
}

void	free_kv_list(t_key_value *list) {
	t_key_value	*temp;

	while (list) {
		temp = list;
		list = list->next;
		free_kv_node(temp);
	}
}

void	delete_kv_node(t_key_value **list, char *key) {
	t_key_value	**prev = list;
	t_key_value	*temp = *list;
	t_key_value	*to_delete = NULL;

	while (temp) {
		if (strcmp(temp->key, key) == 0) {
			to_delete = temp;
			break ;
		}
		prev = &(temp->next);
		temp = temp->next;
	}
	if (!to_delete)
		return ;
	*prev = to_delete->next;
	free_kv_node(to_delete);
	return ;
}
