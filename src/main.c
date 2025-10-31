/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   main.c                                              :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "env.h"

void	exec_config_file(t_env *env);
int		init_env(t_env *env, char **arg_env);
void	interactive_loop(t_env *env);
void	free_double_array(char**);
void	free_kv_list(t_key_value*);

int	main(int ac, char **av, char **arg_env) {
	t_env	env;
	
	(void)av;
	if (ac != 1)
		return (1);
	if (init_env(&env, arg_env) != 0)
		return (1);
	exec_config_file(&env);
	interactive_loop(&env);
	free_kv_list(env.env_list);
	free_kv_list(env.aliases);
	return (0);
}
