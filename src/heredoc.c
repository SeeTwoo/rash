/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   heredoc.c                                           :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*ts_readline(char *prompt);

int	heredoc(char *limiter) {
	int		fds[2];
	char	*line = NULL;

	pipe(fds);
	do {
		free(line);
		line = ts_readline("> ");
		if (!line)
			return (fds[0]);
		dprintf(fds[1], line);
		dprintf(fds[1], "\n");
	} while (strcmp(line, limiter) != 0);
	return (fds[0]);
}
