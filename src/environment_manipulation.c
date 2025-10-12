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
	dest[i] = NULL;
	return (dest);
}
