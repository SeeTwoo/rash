/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   build_prompt.c                                      :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: SeeTwoo <waltibee@gmail.com>                +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>

#include "env.h"

static char	*get_wd(char **env) {
	char	*last_slash;
	char	*wd;

	while (strncmp(*env, "PWD", 3) != 0)
		env++;
	if (!(*env))
		return (NULL);
	wd = *env;
	last_slash = wd;
	while (*wd) {
		if (*wd == '/')
			last_slash = wd;
		wd++;
	}
	if (*last_slash == '/')
		last_slash++;
	return (last_slash);
}

static char	*get_bit(char *format, t_env *env) {
	if (strncmp(format, "wd", 2) == 0)
		return (get_wd(env->env));
	return (NULL);
}

void	build_prompt(char *prompt, char *format, t_env *env) {
	int		total_len;
	int		bit_len;
	char	*bit;

	while (*format && total_len <= 255) {
		if (*format != '%') {
			bit_len = strcspn(format, "%");
			memcpy(&prompt[total_len], format, bit_len);
			total_len += bit_len;
			format += bit_len;
 		} else {
			format++;
			bit = get_bit(format, env);
			bit_len = strlen(bit);
			memcpy(&prompt[total_len], bit, bit_len);
			total_len += bit_len;
			format += 2;
		}
	}
	prompt[total_len] = '\0';
}
