/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_readline.c                                       :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "ts_readline.h"

void	enable_raw_mode(t_settings *original);
void	disable_raw_mode(t_settings *original);

static void	replace_line(char line_buffer[1024], t_ts_hist **history, char cmd) {
	if (cmd == 'A' && (*history)->prev)
		*history = (*history)->prev;
	else if ((*history)->next)
		*history = (*history)->next;
	memcpy(line_buffer, (*history)->line, strlen((*history)->line));
}

static void	arrow_handling(char line_buffer[1024], t_ts_hist **history) {
	char	cmd_buf[3];
	char	cmd;

	read(0, cmd_buf, 3);
	cmd = cmd_buf[2];
	if (strncmp("[[", cmd_buf, 2) != 0 || 
			(cmd != 'A' && cmd != 'B' && cmd != 'C' && cmd != 'D'))
		return ;
	if (cmd == 'A' || cmd == 'B')
		replace_line(line_buffer, history, cmd);
}

static void	fill_line(char line_buffer[1024], char c, int *i) {
	line_buffer[*i] = c;
	write(1, &c, 1);
	(*i)++;
}

char	*ts_readline(char *prompt, t_ts_hist *history) {
	t_settings	original;
	char		line_buffer[1024];
	char		c;
	int			i;

	enable_raw_mode(&original);
	write(1, prompt, strlen(prompt));
	i = 0;
	while (1) {
		dprintf(2, "hey\n");
		read(0, &c, 1);
		if (c == '^')
			arrow_handling(line_buffer, &history);
		else
			fill_line(line_buffer, c, &i);
	}
	disable_raw_mode(&original);
	return (strdup(line_buffer));
}
