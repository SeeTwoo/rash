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
	char		*key;
	char		*value;
	t_kv_list	*next;
};

t_kv_list	*new_kv_node(char *new_kv);
void		add_kv_back(t_kv_list **list, t_kv_list *nev);
int			set_kv_value(t_kv_list *node, char *new, size_t name_len);
t_kv_list	*kv_n_chr(t_kv_list *list, char *key, size_t n);
void		modify_kv_list(t_kv_list **kv, char *new, ssize_t key_len);
char		*get_kv_value(t_kv_list *list, char *key);
char		*get_kv_n_value(t_kv_list *list, char *key, size_t n);
t_kv_list	*kv_chr(t_kv_list *list, char *key);
void		free_kv_node(t_kv_list *node);
void		free_kv_list(t_kv_list *list);
void		delete_kv_node(t_kv_list **list, char *key);

#endif
