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

#include "env.h"

char	**get_paths(char **arg_env);

int	init_env(t_env *env, char **arg_env) {
	env->paths = get_paths(arg_env);
	if (!env->paths)
		return (1);
	env->env = arg_env;
	return (0);
}
