/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   exec_config_file.c                                  :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "key_value.h"
#include "nodes.h"
#include "env.h"
#include "messages.h"

int		script_loop(t_env *env, char *path);

void	exec_config_file(t_env *env) {
	char		config_path[4096];
	char		*home;
	size_t		home_len;

	home = get_kv_value(env->env_list, "HOME");
	if (!home) {
		dprintf(2, "%s%s\n", WARN_HD, NO_HOME_VAR_RC);
		return ;
	}
	home_len = strlen(home);
	memcpy(config_path, home, home_len);
	config_path[home_len] = '/';
	memcpy(&config_path[home_len + 1], ".rashrc", 7);
	config_path[home_len + 1 + 7] = '\0';
	script_loop(env, config_path);
}
