/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   get_command_binary_path.c                           :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "nodes.h"

static size_t	build_temp_path(char temp[4096], char *path, char *name) {
	size_t	path_len = strcspn(path, ":");

	memcpy(temp, path, path_len);
	strcpy(&temp[strlen(path)], "/");
	strcpy(&temp[strlen(path) + 1], name);
	return (path_len);
}

static int	find_command_full_path(char *paths, char *name, char temp[4096]) {
	char	*head;
	int		i;

	i = 0;
	head = paths;
	while (*paths) {
		if (*paths == ':')
			paths++;
		paths += build_temp_path(head, paths, name);
		if (access(temp, X_OK) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	get_bin_path(t_node *node, char *path_variable) {
	char	temp[4096];
	char	*command_path;

	if (!node || !path_variable || !(node->command) || !(node->command[0]))
		return (1);
	if (access(node->command[0], X_OK) == 0)
		return (0);
	if (find_command_full_path(path_variable, node->command[0], temp) == 1)
		return (1);
	command_path = strdup(temp);
	if (!command_path)
		return (1);
	free(node->command[0]);
	node->command[0] = command_path;
	return (0);
}
