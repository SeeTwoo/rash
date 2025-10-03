#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

typedef struct s_redir	t_redir;

struct s_redir {
	char	*name;
	int		type;
	t_redir	*next;
};

#endif
