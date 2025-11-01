/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_unset.c                                          :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "env.h"
#include "nodes.h"

int	tshoo_unset(t_node *cmd, t_env *env) {
	if (!cmd->command[1])
		return (1);
	for (int i = 1; cmd->command[i]; i++) {
		delete_kv_node(&(env->env_list), cmd->command[i]);
	}
	return (0);
}
