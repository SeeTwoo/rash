/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   init_env.c                                          :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "env.h"

void	free_double_array(char **array);
char	**get_paths(char **arg_env);

static size_t	tab_len(char **env) {
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
}

int	init_env(t_env *env, char **arg_env) {
	env->paths = get_paths(arg_env);
	if (!env->paths)
		return (1);
	env->env = envdup(arg_env);
	if (!env->env)
		return (free_double_array(env->paths), 1);
	env->env_var_number = tab_len(env->env);
	env->aliases = NULL;
	env->should_exit = false;
	return (0);
}
