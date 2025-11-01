#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "token.h"
#include "nodes.h"
#include "token_and_node_types.h"

int	is_in_redir(t_token *token);
int	is_out_redir(t_token *token);

void	add_redir(t_redir **tail, t_redir **head, t_token **toks) {
	t_redir *new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	if (!(*head)) {
		*head = new;
		*tail = *head;
	} else {
		(*tail)->next = new;
		*tail = (*tail)->next;
	}
	new->name = NULL;
	new->name = strndup(toks[1]->start, toks[1]->len);
	new->type = toks[0]->type;
	new->next = NULL;
}

int	get_redirections(t_node *node, t_token **toks) {
	t_redir	*in_tail;
	t_redir	*out_tail;

	in_tail = NULL;
	out_tail = NULL;
	while (*toks && (*toks)->type != PIPE) {
		if (is_in_redir(*toks)) {
			add_redir(&in_tail, &(node->in_redir), toks);
			toks += 2;
		} else if (is_out_redir(*toks)) {
			add_redir(&out_tail, &(node->out_redir), toks);
			toks += 2;
		} else {
			toks++;
		}
	}
	return (0);
}
