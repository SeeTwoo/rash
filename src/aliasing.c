/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   aliasing.c                                          :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "env.h"

static size_t	skip_whitespaces(char *line) {
	size_t	i;

	i = 0;
	while (line[i] && isspace(line[i]))
		i++;
	return (i);
}

static size_t	skip_to_next_command_block(char *line) {
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '|')
		i++;
	if (line[i] == '|')
		i++;
	return (i);
}

static char *replace(char *old_line, char *current, char *alias, size_t key_len) {
	char	*line;
	size_t	alias_len;
	size_t	first_half_len;
	char	*last_half;

	alias_len = strlen(alias);
	line = malloc(sizeof(char) * (strlen(old_line) - key_len + alias_len + 1));
	if (!line) {
		dprintf(2, "ts: Warning: an alias was not applied, malloc failed\n");
		return (old_line);
	}
	first_half_len = current - old_line;
	last_half = (char*)(current + key_len);
	memcpy(line, old_line, first_half_len);
	memcpy(line + first_half_len, alias, alias_len);
	memcpy(line + first_half_len + alias_len, last_half, strlen(last_half) + 1);
	free(old_line);
	return (line);
}

static char	*search_and_replace(char *line, char *current, t_kv_list *aliases) {
	char	*alias;
	size_t	key_len;

	key_len = strcspn(current, " \r\t\n<>|");
	alias = get_kv_n_value(aliases, current, key_len);
	if (!alias)
		return (line);
	return (replace(line, current, alias, key_len));
}

char	*aliasing(char *line, t_kv_list *aliases) {
	size_t	current;

	if (!aliases)
		return (line);
	current = 0;
	while (*(line + current)) {
		current += skip_whitespaces(line + current);
		line = search_and_replace(line, (char *)(line + current), aliases);
		current += skip_to_next_command_block(line + current);
	}
	return (line);
}
