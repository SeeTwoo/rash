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

void	add_env_variable(t_kv_list **list, char *new);
void	free_double_array(char **array);
char	**get_paths(char **arg_env);

static t_kv_list *env_to_list(char **env) {
	t_kv_list	*head = NULL;

	while (*env) {
		add_env_variable(&head, *env);
		env++;
	}
	return (head);
}

int	init_env(t_env *env, char **arg_env) {
	env->env_list = env_to_list(arg_env);
	env->history = NULL;
	env->aliases = NULL;
	env->should_exit = false;
	return (0);
}
