#ifndef ENV_H
# define ENV_H

#include "key_value.h"
#include "tshoo_line.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct s_env	t_env;

struct s_env {
	bool			should_exit;
	t_key_value		*aliases;
	t_key_value		*env_list;
	t_tshoo_hist	*history;
};

#endif
