#include <stdlib.h>

#include "token.h"
#include "token_and_node_types.h"

static int	get_type(char current, int len) {
	if (current == '<' && len == 1)
		return (IN);
	else if (current == '<' && len == 2)
		return (HD);
	else if (current == '>' && len == 1)
		return (TRUNC);
	else if (current == '>' && len == 2)
		return (APPEND);
	else if (current == '|' && len == 1)
		return (PIPE);
	return (WRONG);
}

t_token *separator_token(char **line) {
	t_token	*new = malloc(sizeof(t_token));
	char	current = **line;
	int		len = 0;

	if (!new)
		return (NULL);
	while ((*line)[len] == current)
		len++;
	new->start = *line;
	new->len = len;
	new->next = NULL;
	new->type = get_type(current, len);
	(*line) += len;
	return (new);
}
