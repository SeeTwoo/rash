/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   get_next_line.c                                     :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

char	*get_next_line(int fd) {
	static char	buf[BUFFER_SIZE + 1];
	char		*line = NULL;
	ssize_t		bytes;
	char		*nl;
	size_t		len = 0;

	while (1) {
		if (!buf[0]) {
			bytes = read(fd, buf, BUFFER_SIZE);
			if (bytes <= 0)
				return (line);
			buf[bytes] = '\0';
		}
		nl = strchr(buf, '\n');
		size_t	part_len = nl ? (size_t)(nl - buf + 1) : strlen(buf);
		line = realloc(line, len + part_len + 1);
		memcpy(line + len, buf, part_len);
		len += part_len;
		line[len] = '\0';
		if (nl) {
			memmove(buf, nl + 1, strlen(nl + 1) + 1);
			return (line);
		}
		buf[0] = '\0';
	}
}
