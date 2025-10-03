#include "token.h"
#include "token_and_node_types.h"

int	is_pipe(t_token *token) {
	return (token->type == PIPE);
}

int	is_in_redir(t_token *token) {
	return (
		token->type == IN ||
		token->type == HD
	);
}

int	is_out_redir(t_token *token) {
	return (
		token->type == APPEND ||
		token->type == TRUNC
	);
}

int	is_redir(t_token *token) {
	return (
		token->type == IN ||
		token->type == HD ||
		token->type == APPEND ||
		token->type == TRUNC
	);
}

int	is_wrong_token(t_token *token) {
	return (token->type == WRONG);
}

int	is_word(t_token *token) {
	return (token->type == WORD);
}
