#include <stdio.h>
#include <stdlib.h>

char	*ts_readline(char *prompt);

#ifndef PROMPT
# define PROMPT "type something asshole >"
#endif

int	main(void) {
	char	*line;

	line = ts_readline(PROMPT);
	if (!line)
		return (1);
	printf("%s\n", line);
	free(line);
	return (0);
}
