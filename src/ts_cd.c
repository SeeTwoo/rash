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

#include "kv_list.h"
#include "messages.h"
#include "nodes.h"

t_kv_list	*kv_chr(t_kv_list *list, char *key);
int	set_kv_value(t_kv_list *node, char *new, size_t name_len);

int	ts_cd(t_node *node, t_kv_list *env) {
	t_kv_list	*old_pwd = kv_chr(env, "OLDPWD");
	t_kv_list	*pwd = kv_chr(env, "PWD");

	if (chdir(node->command[1]) == -1)
		return (dprintf(2, "%s%s : %s\n", ERR_HD, node->command[1], strerror(errno)), 1);
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = getcwd(NULL, 0);
	if (!(pwd->value))
		dprintf(2, "%s%s", WARN_HD, BROKEN_ENV);
	return (0);
}
