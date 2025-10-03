#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>

typedef struct s_token	t_token;

struct s_token {
	char	*start;
	size_t	len;
	int		type;
	t_token	*next;
};

#endif
