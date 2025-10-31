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

char	**list_to_env(t_key_value *list) {
	char	**dest = malloc(sizeof(char *) * (kv_list_len(list) + 1));
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
