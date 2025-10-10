/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   assign_variable.c                                   :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	assign_variable(t_env *env, char *new) {
	size_t	name_len = strcspn(new, "=");
	size_t	value_len = strlen(&new[name_len + 1]);

	if (name_len == 0)
		return (dprintf(2, "%s%s\n", WARN_HD, NEED_NAME), 0);
	if (value_len == 0)
		return (dprintf(2, "%s%s\n", WARN_HD, NEED_VALUE), 0);

}
