#include "token.h"
#include "token_and_node_types.h"

int	is_redir(t_token *token);

void	set_token_types(t_token **array) {
	for (int i = 0; array[i]; i++) {
		if (is_redir(array[i]))
			array[i + 1]->type = FILE_NAME;
	}
}
