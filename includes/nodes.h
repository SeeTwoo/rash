#ifndef NODES_H
# define NODES_H

#include <sys/types.h>

#include "redirections.h"

typedef struct s_node	t_node;

struct s_node {
	char	**command;
	int		type;
	int		in;
	int		out;
	t_redir	*in_redir;
	t_redir	*out_redir;
	pid_t	pid;
};

#endif
