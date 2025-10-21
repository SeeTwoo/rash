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

char		*get_kv_value(t_kv_list *list, char *key);
t_kv_list	*kv_chr(t_kv_list *list, char *key);
int			set_kv_value(t_kv_list *node, char *new, size_t name_len);

int	array_len(char **array) {
	int	i = 0;

	while (array[i])
		i++;
	return (i);
}
char	*get_destination(t_node *node, t_kv_list *list, int ac) {
	if (ac == 1)
		return (get_kv_value(list, "HOME"));
	else if (ac == 2 && strcmp("-", node->command[1]) == 0)
		return ((kv_chr(list, "OLDPWD"))->value);
	else
		return (node->command[1]);
}

int	ts_cd(t_node *node, t_env *env) {
	t_kv_list	*old_pwd = kv_chr(env->env_list, "OLDPWD");
	t_kv_list	*pwd = kv_chr(env->env_list, "PWD");
	char		*path;
	int			ac = array_len(node->command);

	if (ac > 2)
		return (dprintf(2, "%s%s : %s\n", ERR_HD, "cd", TOO_MANY), 1);
	path = get_destination(node, env->env_list, ac);
	if (!path)
		return (1);
	if (access(path, F_OK) != 0)
		return (1);
	if (chdir(path) == -1)
		return (dprintf(2, "%s%s : %s\n", ERR_HD, node->command[1], strerror(errno)), 1);
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = getcwd(NULL, 0);
	if (!(pwd->value))
		dprintf(2, "%s%s", WARN_HD, BROKEN_ENV);
	return (0);
}
