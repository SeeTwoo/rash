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
#include <string.h>
#include <unistd.h>

#include "kv_list.h"
#include "messages.h"
#include "nodes.h"

int	set_kv_value(t_kv_list *node, char *new, size_t name_len);

int	ts_cd(t_node *node, t_kv_list *env) {
	(void)env;
	//set_kv_value(kv_chr(env, "OLD_PWD"),
	if (chdir(node->command[1]) == -1)
		return (dprintf(2, "%s%s : %s\n", ERR_HD, node->command[1], strerror(errno)), 1);
	return (0);
}
