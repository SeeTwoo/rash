#include <stdio.h>
#include <stdlib.h>

#include "includes/ts_readline.h"

#ifndef PROMPT
# define PROMPT "type something asshole >"
#endif

int	main(void) {
	char	*line;

	line = ts_readline(PROMPT, NULL);
	if (!line)
		return (1);
	printf("%s\n", line);
	free(line);
	return (0);
}
