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

struct s_key_value {
	char		*key;
	char		*value;
	t_key_value	*next;
};

static t_kv_list *env_to_list(char **env) {
	t_kv_list	*head;
	t_kv_list	*tail;

	if (!(*env))
		return (NULL);
	head = new_kv_node(*env);
	tail = head;
	env++;
	while (*env) {
		tail->next = new_kv_node(*env);
		tail = tail->next;
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
