#include <unistd.h>
#include <stdlib.h>

#include "env.h"
#include "nodes.h"

int	tshoo_exit(t_node *cmd, t_env *env) {
	(void)cmd;
	env->should_exit = true;
	return (0);
}
