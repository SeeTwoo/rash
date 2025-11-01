#include <stdio.h>

#include "env.h"
#include "nodes.h"

int	tshoo_env(t_node *cmd, t_env *env) {
	t_key_value	*list = env->env_list;

	(void)cmd;
	while (list) {
		printf("%s=%s\n",get_key(list), get_value(list));
		list = get_next(list);
	}
	fflush(stdout);
	return (0);
}
