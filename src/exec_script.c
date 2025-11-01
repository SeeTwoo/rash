#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nodes.h"
#include "env.h"

char	*aliasing(char *line, t_key_value *aliases);
int		exec(t_node **nodes, t_env *env);
void	free_node_array(t_node **nodes);
t_node	**parse_line(char *line);
int		process_line(char *line, t_env *env);
