#ifndef ENV_H
# define ENV_H

#include "kv_list.h"
#include "tshoo_line.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct s_env	t_env;

struct s_env {
	bool			should_exit;
	t_kv_list		*aliases;
	t_kv_list		*env_list;
	t_tshoo_hist	*history;
};

#endif
