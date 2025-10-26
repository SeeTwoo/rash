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

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

char	*dir_substring(char *file_name, char *last_slash) {
	if (!last_slash)
		return (strdup("."));
	else
		return (strndup(file_name, last_slash - file_name + 1));
}

char	*name_substring(char *file_name, char *last_slash) {
	if (!last_slash)
		return (strdup(file_name));
	else
		return (strdup(last_slash + 1));
}

char	*find_match(char *file_name) {
	char			*last_slash;
	char			*dir_name;
	char			*foot;
	size_t			foot_len;
	DIR				*dir;
	struct dirent	*entry;

	last_slash = strrchr(file_name, '/');
	dir_name = dir_substring(file_name, last_slash);
	foot = name_substring(file_name, last_slash);
	foot_len = strlen(foot);
	dir = opendir(dir_name);
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry) {
		if (strncmp(entry->d_name, foot, foot_len) == 0)
			return (entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

int	main(int ac, char **av) {
	if (ac != 2)
		return (1);
	char	*match;

	match = find_match(av[1]);
	if (!match)
		return (printf("\x1b[1;31m no match ! \x1b[0m\n"), 1);
	printf("%s\n", match);
	return (0);
}
