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

#include "env.h"

int		init_env(t_env *env, char **arg_env);
void	main_loop(t_env *env);
void	free_double_array(char**);
void	free_kv_list(t_kv_list*);

int	main(int ac, char **av, char **arg_env) {
	t_env			env;
	//unsigned long	start_time;
	//unsigned long	setup_end_time;
	
	(void)av;
	//start_time = get
	if (ac != 1)
		return (1);
	if (init_env(&env, arg_env) != 0)
		return (1);
	main_loop(&env);
	free_double_array(env.paths);
	free_kv_list(env.aliases);
	return (0);
}
