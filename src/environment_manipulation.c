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
<<<<<<< HEAD
#include "kv_list.h"

static size_t	listlen(t_kv_list *list) {
	size_t	i;

	i = 0;
	while (list) {
		list = list->next;
		i++;
	}
	return (i);
}
=======
>>>>>>> e48c020 (done including the key_value separate library for environment and aliases)

static char	*build_env_line(char *key, char *value) {
	size_t	key_len = strlen(key);
	char	*dest = malloc(sizeof(char) * (key_len + strlen(value) + 2));

	if (!dest)
		return (NULL);
	strcpy(dest, key);
	strcpy(&dest[key_len], "=");
	strcpy(&dest[key_len + 1], value);
	return (dest);
}

<<<<<<< HEAD
char	**list_to_env(t_kv_list *list) {
	char	**dest = malloc(sizeof(char *) * (listlen(list) + 1));
=======
char	**list_to_env(t_key_value *list) {
	char	**dest = malloc(sizeof(char *) * (kv_list_len(list) + 1));
>>>>>>> e48c020 (done including the key_value separate library for environment and aliases)
	size_t	i = 0;
	
	if (!dest)
		return (NULL);
	while (list) {
		dest[i] = build_env_line(get_key(list), get_value(list));
		list = get_next(list);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
