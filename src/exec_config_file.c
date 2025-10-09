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

#include "nodes.h"
#include "env.h"

void	exec_script(t_env *env, char *path);

void	exec_config_file(t_env *env) {
	char	config_path[4096];
	char	*home;
	size_t	i;
	size_t	home_len;

	i = 0;
	while (env->env[i]) {
		if (strncmp("HOME=", env->env[i], 5) == 0)
			break ;
		i++;
	}
	if (!env->env[i])
		return ;
	home = strchr(env->env[i], '=') + 1;
	home_len = strlen(home);
	memcpy(config_path, home, home_len);
	config_path[home_len] = '/';
	memcpy(&config_path[home_len + 1], ".rashrc", 7);
	config_path[home_len + 1 + 7] = '\0';
	exec_script(env, config_path);
}
