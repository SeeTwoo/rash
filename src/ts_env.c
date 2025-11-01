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
#include "nodes.h"

int	ts_env(t_node *cmd, t_env *env) {
	t_key_value	*list = env->env_list;

	(void)cmd;
	while (list) {
		printf("%s=%s\n",get_key(list), get_value(list));
		list = get_next(list);
	}
	fflush(stdout);
	return (0);
}
