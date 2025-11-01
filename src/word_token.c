#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"
#include "token_and_node_types.h"

static int	isseparator(char c) {
	return (
		c == '<' ||
		c == '>' ||
		c == '|'
	);
}

static int	quote_to_quote_len(char *line) {
	int		i = 0;
	char	quote = line[0];

	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		i++;
	return (i);
}

static size_t	tok_len(char **line) {
	size_t	i;
	
	i = 0;
	while (1) {
		if (!(*line)[i] || isspace((*line)[i]) || isseparator((*line)[i]))
			break ;
		else if ((*line)[i] == '\'' || (*line)[i] == '\"')
			i += quote_to_quote_len(&(*line)[i]);
		else
			i++;
	}
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
