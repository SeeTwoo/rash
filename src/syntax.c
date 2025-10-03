/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   syntax.c                                            :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

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
		if (is_pipe(tok_array[i]) &&
				(i == 0 || !tok_array[i + 1] || is_pipe(tok_array[i + 1]))) {
			printf("unclosed pipe\n");
			return (0);
		}
		if (is_redir(tok_array[i]) &&
				(!tok_array[i + 1] || !is_word(tok_array[i + 1]))) {
			printf("redirection needs to be followed by a word\n");
			return (0);
		}
		if (is_wrong_token(tok_array[i])) {
			printf("token not recognized : ");
			write(2, tok_array[i]->start, tok_array[i]->len);
			write(2, "\n", 1);
			return (0);
		}
		i++;
	}
	return (1);
}
