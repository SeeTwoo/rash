/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   quote_trim.c                                        :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "nodes.h"

static size_t	skip_quoted(const char **s, char quote) {
	size_t	len = 0;

	while (**s && **s != quote)
		(*s)++, len++;
	if (**s == quote)
		(*s)++;
	return (len);
}

size_t	no_quote_size(const char *s) {
	size_t	size = 0;

	while (*s) {
		if (*s == '\'' || *s == '\"')
			size += skip_quoted(&s, *s);
		else
			s++, size++;
	}
	return (size);
}

void	no_quote_fill(char *dest, char *src) {
	char	quote;

	while (*src) {
		if (*src == '\'' || *src == '\"') {
			quote = *src++;
			while (*src && *src != quote)
				*dest++ = *src++;
			if (*src == quote)
				src++;
		} else {
			*dest++ = *src++;
		}
	}
	*dest = '\0';
}

char	*trim_string(char *s) {
	char	*dest;

	dest = malloc(sizeof(char) * (no_quote_size(s) + 1));
	if (!dest)
		return (NULL);
	no_quote_fill(dest, s);
	return (dest);
}

int	trim_command(t_node *node) {
	char	**cmd;
	char	*temp;

	cmd = node->command;
	for (int i = 0; cmd[i]; i++) {
		temp = trim_string(cmd[i]);
		if (!temp)
			continue ;
		free(cmd[i]);
		cmd[i] = temp;
		temp = NULL;
	}
	return (0);
}
