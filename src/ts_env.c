/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_env.c                                            :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "env.h"

int	ts_env(t_kv_list *list) {
	while (list) {
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	fflush(stdout);
	return (0);
}
