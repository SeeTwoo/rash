/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_readline.h                                       :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef TS_READLINE_H
# define TS_READLINE_H

typedef struct s_ts_hist	t_ts_hist;

struct s_ts_hist {
	t_ts_hist	*prev;
	t_ts_hist	*next;
	char		*line;
};

char	*ts_readline(char *prompt, t_ts_hist *history);
int		ts_add_hist(char *line, t_ts_hist *history);
void	free_history(t_ts_hist *history);

#endif
