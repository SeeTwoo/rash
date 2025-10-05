/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   free_history.c                                      :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "ts_readline.h"

void	free_history(t_ts_hist *history) {
	t_ts_hist	*temp;

	while (history) {
		temp = history;
		history = history->next;
		free(temp->line);
		free(temp);
	}
}
