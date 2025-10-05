#include <string.h>
#include <unistd.h>

char	*ts_readline(char *prompt) {
	size_t	bytes_read;
	char	buffer[1024];

	write(1, prompt, strlen(prompt));
	bytes_read = 0;
	do {
		bytes_read += read(0, buffer, 1023 - bytes_read);
		buffer[bytes_read] = '\0';
	} while (!strchr(buffer, '\n') && bytes_read <= 1023);
	if (buffer[bytes_read - 1] == '\n')
		buffer[bytes_read - 1] = '\0';
	return (strdup(buffer));
}
