#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tshoo_line.h"

int	heredoc(char *limiter) {
	int		fds[2];
	char	*line = NULL;

	pipe(fds);
	do {
		free(line);
		line = tshoo_line("> ", NULL);
		if (!line)
			return (fds[0]);
		dprintf(fds[1], "%s", line);
		dprintf(fds[1], "\n");
	} while (strcmp(line, limiter) != 0);
	return (fds[0]);
}
