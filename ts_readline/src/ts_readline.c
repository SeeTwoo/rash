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

#include <ctype.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "ts_readline.h"

typedef struct s_rl	t_rl;

struct s_rl {
	char		line[1024];
	int			i;
	int			len;
};

void	enable_raw_mode(t_settings *original);
void	disable_raw_mode(t_settings *original);

/*static void	replace_line(t_rl *rl, t_ts_hist **history, char cmd) {
	if (cmd == 'A' && (*history)->prev)
		*history = (*history)->prev;
	else if ((*history)->next)
		*history = (*history)->next;
	memcpy(rl->line, (*history)->line, strlen((*history)->line));
}
*/

static void	fill_command(char *cmd_buf, char *cmd) {
	int	i;

	i = 0;
	while (1) {
		if (read(0, &cmd_buf[i], 1) == 0)
			continue ;
		if (isalpha(cmd_buf[i]))
			break ;
		i++;
	}
	*cmd = cmd_buf[i];
	i++;
	cmd_buf[i] = '\0';
}

static void cursor_left_right(t_rl *rl, int inc) {
	if (rl->i + inc >= 1022 || rl->i + inc <= 0)
		return ;
	if (inc == -1)
		write(2, "\x08", 1);
	else
		write(2, "\x1b[C", 3);
	rl->i += inc;
}

static void	arrow_handling(t_rl *rl, t_ts_hist **history) {
	char	cmd_buf[32];
	char	cmd;

	(void)history;
	fill_command(cmd_buf, &cmd);
	if (cmd != 'A' && cmd != 'B' && cmd != 'C' && cmd != 'D')
		return ;
	//if (cmd == 'A' || cmd == 'B')
	//	replace_line(line_buffer, history, cmd);
	if (cmd == 'C' || cmd == 'D')
		cursor_left_right(rl, cmd = 'C' ? -1 : 1);
}

static void	fill_line(t_rl *rl, char c) {
	write(2, "\x1b[K", 3);
	memmove(&rl->line[rl->i + 1], &rl->line[rl->i], 1022 - rl->i);
	rl->line[rl->i] = c;
	write(2, &rl->line[rl->i], strlen(&rl->line[rl->i]));
	rl->i++;
	rl->len++;
}

static void	backspace_handling(t_rl *rl) {
	if (rl->i == 0)
		return ;
	rl->line[rl->i] = '\0';
	rl->i++;
	rl->len++;
	write(2, "\x08\x1b[K", 4);
}

char	*ts_readline(char *prompt, t_ts_hist *history) {
	t_settings	original;
	char		c;
	t_rl		rl;

	enable_raw_mode(&original);
	write(2, prompt, strlen(prompt));
	rl.i = 0;
	rl.len = 0;
	rl.line[0] = '\0';
	while (1) {
		if (read(0, &c, 1) == 0)
			continue ;
		else if (c == '\r' || rl.len == 1023)
			break ;
		else if (c == '\x7f')
			backspace_handling(&rl);
		else if (c == '\x1b')
			arrow_handling(&rl, &history);
		else
			fill_line(&rl, c);
	}
	rl.line[rl.len] = '\0';
	write(2, "\r\v", 2);
	disable_raw_mode(&original);
	return (strdup(rl.line));
}
