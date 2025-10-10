#ifndef ENV_H
# define ENV_H

#include "kv_list.h"
#include "ts_readline.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct s_env	t_env;

struct s_env {
	char		**paths;
	char		**env;
	size_t		env_var_number;
	bool		should_exit;
	t_kv_list	*aliases;
	t_ts_hist	*history;
};

#endif
