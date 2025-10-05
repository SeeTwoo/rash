/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   aliases.h                                           :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef KV_LIST_H 
# define KV_LIST_H

typedef struct s_kv_list	t_kv_list;

struct s_kv_list {
	char		*raw;
	char		*key;
	char		*value;
	t_kv_list	*next;
};

#endif
