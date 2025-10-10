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

typedef struct s_prompt	t_prompt;

struct s_prompt {
	char	*temp;
	char	*format;
};

void	fill_prompt(char *prompt, size *size, char *format) {
	size_t	offset;

	offset = strcspn(format, "%");
	memcpy(prompt, format, offset);

}

void	expand_format(char *prompt, size *size, char *format) {
	
}

void	build_prompt(char *prompt, char *format) {
	t_prompt	vars;

	vars->temp = prompt;
	vars->format = format;
	while (*format && vars->temp - ) {
		if (*format != '%')
			format += fill_prompt(prompt, &size, format);
		else
			format += expand_format(prompt, &size, format);
	}
}
