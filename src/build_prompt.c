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

/*typedef struct s_prompt	t_prompt;

struct s_prompt {
	char	*temp;
	char	*format;
	size_t	size;
	bool	continue;
};*/

char	*get_wd(char **env) {
	char	*last_slash;
	while (strncmp(*env, "PWD", 3) != 0)
		env++;
	if (!(*env))
		return (NULL);
	while (
}

char	*get_bit(char *format, t_env *env) {
	if (strncmp(format, "wd", 2) == 0)
		return (get_wd(env->env));
}

void	build_prompt(char *prompt, char *format, t_env *env) {
	int		total_len;
	int		bit_len;
	char	*bit;

	while (*format && len <= 255) {
		if (format != '%') {
			bit_len = strcspn(format, "=");
			memcpy(&prompt[total_len], format, bit_len);
			total_len += bit_len;
			format += bit_len;
 		} else {
			format++;
			bit = get_bit(format, env);
		}
	}
}
