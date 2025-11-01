#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "token_and_node_types.h"

char	**tok_to_args(t_token **tok_array) {
	char	**command;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tok_array[i] && tok_array[i]->type != PIPE) {
		if (tok_array[i]->type == WORD)
			j++;
		i++;
	}
	command = malloc(sizeof(char *) * (j + 1));
	if (!command)
		return (NULL);
	i = 0;
	j = 0;
	while (tok_array[i] && tok_array[i]->type != PIPE) {
		if (tok_array[i]->type == WORD) {
			command[j] = strndup(tok_array[i]->start, tok_array[i]->len);
			j++;
		}
		i++;
	}
	command[j] = NULL;
	return (command);
}
