/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_cd.c                                             :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "messages.h"
#include "nodes.h"

struct s_key_value {
	char		*key;
	char		*value;
	t_key_value *next;
};

int	array_len(char **array) {
	int	i = 0;

	while (array[i])
		i++;
	return (i);
}

char	*get_destination(t_node *node, t_key_value *list, int ac) {
	char	*destination;

	if (ac == 1) {
		destination = get_kv_value(list, "HOME");
		if (!destination)
			dprintf(2, "%s%s\n", WARN_HD, HOME_NOT_SET);
	} else if (ac == 2 && strcmp("-", node->command[1]) == 0) {
		destination = get_kv_value(list, "OLDPWD");
		if (!destination)
			dprintf(2, "%s%s\n", WARN_HD, OLDPWD_NOT_SET);
	} else {
		destination = node->command[1];
	}
	return (destination);
}

int	ts_cd(t_node *node, t_env *env) {
	t_kv_list	*old_pwd = kv_chr(env->env_list, "OLDPWD");
	t_kv_list	*pwd = kv_chr(env->env_list, "PWD");
	char		*path;
	int			len = 0;

	while (node->command[len])
		len++;
	if (len > 2)
		return (dprintf(2, "%s%s : %s\n", ERR_HD, "cd", TOO_MANY), 1);
	if (len == 1)
		path = get_kv_value(env->env_list, "HOME");
	else if (len == 2 && strcmp("-", node->command[1]) == 0)
		path = old_pwd->value;
	else if (len == 2)
		path = node->command[1];
	if (chdir(path) == -1)
		return (dprintf(2, "%s%s : %s\n", ERR_HD, node->command[1], strerror(errno)), 1);
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = getcwd(NULL, 0);
	if (!(pwd->value))
		dprintf(2, "%s%s", WARN_HD, BROKEN_ENV);
	return (0);
}
