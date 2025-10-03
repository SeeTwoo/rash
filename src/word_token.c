/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   word_token.c                                        :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"
#include "token_and_node_types.h"

int	isseparator(char c) {
	return (
		c == '<' ||
		c == '>' ||
		c == '|'
	);
}

size_t	tok_len(char **line) {
	size_t	i;
	
	i = 0;
	while ((*line)[i] && !isspace((*line)[i]) && !isseparator((*line)[i]))
		i++;
	(*line) += i;
	return (i);
}

t_token	*word_token(char **line) {
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->start = *line;
	new->len = tok_len(line);
	new->next = NULL;
	new->type = WORD;
	return (new);
}
