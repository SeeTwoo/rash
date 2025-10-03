/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   get_paths.c                                         :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char	**free_paths(char **paths, int i) {
	while (i >= 0) {
		free(paths[i]);
		i--;
	}
	free(paths);
	return (NULL);
}

static char	*find_path_variable(char **envp) {
	int	i;

	i = 0;
	while (strncmp("PATH=", envp[i], 5))
		i++;
	return (&envp[i][5]);
}

static int	count_paths(char *path_variable) {
	int	count;

	count = 0;
	while (*path_variable) {
		path_variable += strspn(path_variable, ":");
		if (!(*path_variable))
			break ;
		count++;
		path_variable += strcspn(path_variable, ":");
	}
	return (count);
}

char	**get_paths(char **envp) {
	char	*path_variable;
	int		path_number;
	char	**paths;
	size_t	path_len;
	int		i;

	path_variable = find_path_variable(envp);
	path_number = count_paths(path_variable);
	paths = malloc(sizeof(char *) * (path_number + 1));
	if (!paths)
		return (NULL);
	i = 0;
	while (*path_variable) {
		path_variable += strspn(path_variable, ":");
		if (!(*path_variable))
			break ;
		path_len = strcspn(path_variable, ":");
		paths[i] = strndup(path_variable, path_len);
		if (!paths[i])
			return (free_paths(paths, i));
		path_variable += path_len;
		i++;
	}
	paths[i] = NULL;
	return (paths);
}
