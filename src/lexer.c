/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   lexer.c                                             :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

t_token	*word_token(char **line);
t_token	*separator_token(char **line);
void	free_token_list(t_token *head);

static void	skip_whitespaces(char **line) {
	while (isspace(**line))
		(*line)++;
}

t_token	*lexer(char *line) {
	t_token	*head;
	t_token	*tail;

	head = NULL;
	tail = NULL;
	skip_whitespaces(&line);
	if (!(*line))
		return (NULL);
	if (*line == '<' || *line == '>' || *line == '|')
		head = separator_token(&line);
	else
		head = word_token(&line);
	if (!head)
		return (NULL);
	tail = head;
	while (*line) {
		skip_whitespaces(&line);
		if (*line == '<' || *line == '>' || *line == '|')
			tail->next = separator_token(&line);
		else
			tail->next = word_token(&line);
		if (!tail->next)
			return (free_token_list(head), NULL);
		tail = tail->next;
	}
	return (head);
}
