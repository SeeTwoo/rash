/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   list_to_array.c                                     :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"

static size_t	list_len(t_token *tok_list) {
	size_t	len;

	len = 0;
	while (tok_list) {
		tok_list = tok_list->next;
		len++;
	}
	return (len);
}

t_token	**list_to_array(t_token *tok_list) {
	size_t	tok_count;
	size_t	i;
	t_token	**tok_array;

	tok_count = list_len(tok_list);
	tok_array = malloc(sizeof(t_token *) * (tok_count + 1));
	if (!tok_array)
		return (NULL);
	i = 0;
	while (i < tok_count) {
		tok_array[i] = tok_list;
		tok_list = tok_list->next;
		i++;
	}
	tok_array[i] = NULL;
	return (tok_array);
}
