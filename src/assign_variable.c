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

void	modify_kv_list(t_kv_list *kv, char *new, ssize_t key_len);

static ssize_t	is_valid_variable(char *new) {
	ssize_t	key_len;

	if (!strchr(new, '='))
		return (dprintf(2, "%s%s\n", WARN_HD, NEED_EQUAL), -1);
	key_len = strcspn(new, "=");
	if (key_len == 0)
		return (dprintf(2, "%s%s\n", WARN_HD, NEED_NAME), -1);
	return (key_len);
}

void	assign_variable(t_env *env, char *new) {
	ssize_t	key_len;

	key_len = is_valid_variable(new);
	if (key_len == -1)
		return ;
	modify_kv_list(env->env_list, new, key_len);
}
