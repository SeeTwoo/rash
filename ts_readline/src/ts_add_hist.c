/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_add_hist.c                                       :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ts_readline.h"

t_ts_hist	*new_hist_node(char *line, t_ts_hist *prev) {
	t_ts_hist	*new;

	new = malloc(sizeof(t_ts_hist));
	if (!new)
		return (NULL);
	new->prev = prev;
	new->next = NULL;
	new->line = strdup(line);
	if (!new->line)
		return (free(new), NULL);
	return (new);
}

int	ts_add_hist(char *line, t_ts_hist *history) {
	if (!history) {
		history = new_hist_node(line, NULL);
		if (!history)
			dprintf(2, "Couldn't add the line [ %s ] to the history, malloc failed\n", line);
		return (0);
	}
	while (history->next)
		history = history->next;
	history->next = new_hist_node(line, history);
	if (!history->next)
		dprintf(2, "Couldn't add the line [ %s ] to the history, malloc failed\n", line);
	return (0);
}
