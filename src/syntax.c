#include <stdio.h>
#include <unistd.h>

#include "messages.h"
#include "token.h"
#include "nodes.h"
#include "token_and_node_types.h"

int	is_pipe(t_token *token);
int	is_redir(t_token *token);
int	is_wrong_token(t_token *token);
int	is_word(t_token *token);

int	is_syntaxically_correct(t_token **tok_array) {
	int	i;

	i = 0;
	while (tok_array[i]) {
		if (is_pipe(tok_array[i]) && (i == 0 || !tok_array[i + 1] || is_pipe(tok_array[i + 1]))) {
			dprintf(2, "%s%s\n", ERR_HD, UNCLOSED_PIPE);
			return (0);
		}
		if (is_redir(tok_array[i]) && (!tok_array[i + 1] || !is_word(tok_array[i + 1]))) {
			dprintf(2, "%s[%.*s] %s\n", ERR_HD, (int)tok_array[i]->len, tok_array[i]->start, REDIR_FILE_NAME);
			return (0);
		}
		if (is_wrong_token(tok_array[i])) {
			dprintf(2, "%s[%.*s] %s\n", ERR_HD, (int)tok_array[i]->len, tok_array[i]->start, UNKNOWN_TOK);
			return (0);
		}
		i++;
	}
	return (1);
}
