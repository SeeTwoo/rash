/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   environment_manipulation.c                          :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "env.h"
#include "kv_list.h"

char	*get_path(t_env *env) {
	t_kv_list	*temp;

	if (!env)
		return (NULL);
	temp = env->env_list;
	if (!temp)
		return (NULL);
	while (temp && strcmp(temp->key, "PATH") != 0)
		temp = temp->next;
	if (!temp)
		return (NULL);
	return (temp->value);
}

static size_t	listlen(t_kv_list *list) {
	size_t	i;

	i = 0;
	while (list) {
		list = list->next;
		i++;
	}
	return (i);
}

char	**list_to_env(t_kv_list *list) {
	char	**dest = malloc(sizeof(char *) * (listlen(list) + 1));
	size_t	i = 0;
	
	if (!dest)
		return (NULL);
	while (list) {
		dest[i] = strdup(list->raw);
		list = list->next;
		i++;
	}
	return (dest);
}

t_kv_list	*new_env_node(char *s) {
	t_kv_list	*new;
	size_t		key_len;

	new = malloc(sizeof(t_kv_list));
	if (!new)
		return (NULL);
	new->raw = strdup(s);
	if (!new->raw)
		return (free(new), NULL);
	key_len = strcspn(s, "=");
	new->key = strndup(s, key_len);
	if (!new->key)
		return (free(new->raw), free(new), NULL);
	new->value = strdup(&s[key_len + 1]);
	if (!new->value)
		return (free(new->key), free(new->raw), free(new), NULL);
	new->next = NULL;
	return (new);
}

void	add_env_variable(t_kv_list **head, char *s) {
	t_kv_list	*tail;

	if (*head == NULL) {
		*head = new_env_node(s);
		return ;
	}
	tail = *head;
	while (tail->next)
		tail = tail->next;
	tail->next = new_env_node(s);
}

/*static size_t	tab_len(char **env) {
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static void	free_tab(char **env, int i) {
	i--;
	while (i >= 0) {
		free(env[i]);
		i--;
	}
	free(env);
}

static char	**envdup(char **env) {
	char	**new = malloc(sizeof(char *) * tab_len(env));
	size_t	i = 0;

	if (!new)
		return (NULL);
	while (env[i]) {
		new[i] = strdup(env[i]);
		if (!new[i])
			return (free_tab(env, (int)i), NULL);
		i++;
	}
	new[i] = NULL;
	return (new);
}*/
