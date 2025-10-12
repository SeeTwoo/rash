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

void	assign_variable(t_env *env, char *new) {
	size_t		name_len = strcspn(new, "=");
	t_kv_list	*to_modify;

	if (name_len == 0) {
		dprintf(2, "%s%s\n", WARN_HD, NEED_NAME);
		return ;
	}
	to_modify = kv_n_chr(env->env_list, new, name_len);
	if (to_modify)
		set_kv_value(to_modify, new, name_len);
	else
		add_kv_back(&(env->env_list), new);
}
