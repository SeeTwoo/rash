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

char	**arrchr(char **array, char *str, size_t name_len) {
	for (int i = 0; array[i]; i++)
		if (strncmp(array[i], str, name_len) == 0)
			return (&array[i]);
	return (NULL);
}

void	set_env(t_env *env, char *new, char **to_replace) {
	char	*new_entry;

	(void)env;
	new_entry = strdup(new);
	if (!new_entry)
		return ;
	free(*to_replace);
	*to_replace = new_entry;
}

void	add_env(t_env *env, char *new) {
	char	**new_env = malloc(sizeof(char *) * (env->env_var_number + 2));
	char	*new_var = strdup(new);
	size_t	i;

	if (!new_env || !new_var) {
		free(new_env);
		free(new_var);
		return ;
	}
	i = 0;
	while (env->env[i]) {
		new_env[i] = env->env[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(env->env);
	env->env = new_env;
	env->env_var_number += 1;
}

void	assign_variable(t_env *env, char *new) {
	size_t	name_len = strcspn(new, "=");
	char	**variable;

	if (name_len == 0) {
		dprintf(2, "%s%s\n", WARN_HD, NEED_NAME);
		return ;
	}
	variable = arrchr(env->env, new, name_len);
	if (variable)
		set_env(env, new, variable);
	else
		add_env(env, new);
}
