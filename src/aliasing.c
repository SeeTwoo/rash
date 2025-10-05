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

static char	*search_key(char *line, t_kv_list *aliases) {
	while (aliases && strncmp(line, aliases->key, strlen(aliases->key)) != 0)
		aliases = aliases->next;
	if (!aliases)
		return (NULL);
	return (aliases->value);
}

static char *replace_cmd_with_alias(char *old_line, char *alias, size_t cmd_position) {
	size_t	cmd_len;
	size_t	alias_len;
	char	*new_line;
	char	*alias_dest;
	char	*line_end_dest;
	char	*old_line_end;

	cmd_len = strcspn(&old_line[cmd_position], " \t\r|");
	alias_len = strlen(alias);
	new_line = malloc(sizeof(char) * (strlen(old_line) - cmd_len + alias_len + 1));
	if (!new_line) {
		dprintf(2, "ts: Warning: an alias was not applied, malloc failed\n");
		return (old_line);
	}
	alias_dest = &new_line[cmd_position];
	line_end_dest = &new_line[cmd_position + alias_len];
	old_line_end = &old_line[cmd_position + cmd_len];
	memcpy(new_line, old_line, cmd_position);
	memcpy(alias_dest, alias, alias_len);
	memcpy(line_end_dest, old_line_end, strlen(old_line_end) + 1);
	free(old_line);
	return (new_line);
}

static char	*search_and_replace_pattern(char *line, size_t cmd_position, t_kv_list *aliases) {
	char	*alias;

	alias = search_key(line, aliases);
	if (!alias)
		return (line);
	return (replace_cmd_with_alias(line, alias, cmd_position));
}

char	*aliasing(char *line, t_kv_list *aliases) {
	size_t		cmd_position;

	if (!aliases)
		return (line);
	cmd_position = 0;
	while (line[cmd_position]) {
		cmd_position += skip_whitespaces(&line[cmd_position]);
		line = search_and_replace_pattern(line, cmd_position, aliases);
		cmd_position += skip_to_next_command_block(&line[cmd_position]);
	}
	return (line);
}
