#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "env.h"
#include "messages.h"

struct s_key_value {
	char		*key;
	char		*value;
	t_key_value	*next;
};

static t_key_value *env_to_list(char **env) {
	t_key_value	*head;
	t_key_value	*tail;

///	int		i = 0;

	if (!(*env))
		return (NULL);
	head = new_kv_node(*env);
	if (!head)
		return (dprintf(2, "%s%s\n", WARN_HD, NO_ENV), NULL);
	tail = head;
	env++;
	while (*env) {
//		if (i >= 4)
//			tail->next = NULL;
//		else
		tail->next = new_kv_node(*env);
		if (!(tail->next))
			return (dprintf(2, "%s%s\n", WARN_HD, NO_ENV), head);
		tail = tail->next;
		env++;
	//	i++;
	}
	return (head);
}

int	init_env(t_env *env, char **arg_env) {
	env->env_list = env_to_list(arg_env);
	env->history = NULL;
	env->aliases = NULL;
	env->should_exit = false;
	return (0);
}
