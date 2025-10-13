/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   cleaning.c                                          :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "env.h"
#include "nodes.h"
#include "token.h"
#include "redirections.h"

void	free_kv_node(t_kv_list *node) {
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_kv_list(t_kv_list *list) {
	t_kv_list	*temp;

	while (list) {
		temp = list;
		list = list->next;
		free_kv_node(temp);
	}
}

void	close_all_fds(int *fds, int command_number) {
	for (int i = 0; i < command_number; i++) {
		close(fds[i * 2]);
		close(fds[i * 2 + 1]);
	}
}

void	close_every_fd(void) {
	for (int i = 3; i <= 1023; i++)
		close(i);
}

void	free_double_array(char **array) {
	for (int i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

void	free_redir_node(t_redir *node) {
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	free(node);
}

void	free_list_redir(t_redir *head) {
	t_redir	*temp;

	while (head) {
		temp = head;
		head = head->next;
		free_redir_node(temp);
	}
}

void	free_node(t_node *node) {
	if (!node)
		return ;
	if (node->command)
		free_double_array(node->command);
	if (node->in_redir)
		free_list_redir(node->in_redir);
	if (node->out_redir)
		free_list_redir(node->out_redir);
	free(node);
}

void	free_node_array(t_node **nodes) {
	for (int i = 0; nodes[i]; i++)
		if (nodes[i])
			free_node(nodes[i]);
	free(nodes);
}

void	free_token_array(t_token **tok_array) {
	for (int i = 0; tok_array[i]; i++)
		free(tok_array[i]);
	free(tok_array);
}

void	free_token_list(t_token *head) {
	t_token	*temp;

	while (head) {
		temp = head;
		head = head->next;
		free(temp);
	}
}
