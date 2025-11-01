#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "key_value.h"
#include "nodes.h"
#include "env.h"
#include "messages.h"

int		script_loop(t_env *env, char *path);

#ifndef RC_FILE
# define RC_FILE "/.tshoorc"
#endif

void	exec_config_file(t_env *env) {
	char		*config_path;
	char		*home = get_kv_value(env->env_list, "HOME");
	size_t		home_len;

	if (!home) {
		dprintf(2, "%s%s, %s\n", WARN_HD, NO_HOME, NO_RC);
		return ;
	}
	home_len = strlen(home);
	config_path = malloc(sizeof(char) * (home_len + strlen(RC_FILE) + 1));
	if (!config_path) {
		dprintf(2, "%s%s, %s\n", WARN_HD, ERR_MALLOC, NO_RC);
		return ;
	}
	strcpy(config_path, home);
	strcpy(config_path + home_len, RC_FILE);
	script_loop(env, config_path);
	free(config_path);
}
