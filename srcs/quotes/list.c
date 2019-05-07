/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:34:02 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/07 09:36:55 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote.h"

void	init_token_list(t_token_list *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->node_count = 0;
}

/*
** if ((token = (t_token *)malloc(sizeof(t_token))) == NULL)
**		return ;
** This should not happen ever, if it did then we are in trouble
*/

void	push_token(t_token_list *list, char *tok, enum token_type type)
{
	t_token *token;

	if ((token = (t_token *)malloc(sizeof(t_token))) == NULL)
		return ;
	token->token = tok;
	token->tok_type = type;
	token->next = NULL;
	if (list->head == NULL)
	{
		list->head = token;
		list->tail = token;
	}
	else
	{
		list->tail->next = token;
		list->tail = token;
	}
	list->node_count++;
}

/*
** Delete a node from a list of tokens
*/

void	delete_token(t_token_list *list, t_token *tofind)
{
	t_token *current;
	t_token	*prev;

	current = list->head;
	prev = NULL;
	while (current)
	{
		if (current == tofind)
		{
			if (current != list->head && current != list->tail)
				prev->next = current->next;
			else
			{
				if (current == list->head)
					list->head = current->next;
				if (current == list->tail)
					list->tail = prev;
			}
			free_token(current);
			list->node_count--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	free_token_list(t_token_list *list)
{
	t_token *current;
	t_token *tmp;

	current = list->head;
	while (current)
	{
		ft_strdel(&current->token);
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free(list);
}

char			**list_to_chars(t_token *node)
{
	char		**cmds;
	int			count;
	t_token		*copy;

	count = 0;
	copy = node;
	while (copy && !(node->tok_type & SH_SEMI) && !(node->tok_type & SH_PIPE))
	{
		count++;
		copy = copy->next;
	}
	cmds = (char**)ft_memalloc(sizeof(char*) * (count + 1));
	if (cmds == NULL)
		return (NULL);
	count = 0;
	while (node)
	{
		if ((node->tok_type & SH_SEMI) || (node->tok_type & SH_PIPE))
			break ;
		if (node->tok_type & SH_WORD)
			cmds[count++] = ft_strdup(node->token);
		node = node->next;
	}
	cmds[count] = NULL;
	return (cmds);
}

char	*enum_char(enum token_type type)
{
	char	*name;

	if (type & SH_WORD)
	{
		name = "SH_WORD";
		if (type & SH_QUOTED)
			name = "SH_WORD SH_QUOTE";
		else if (type & SH_REDIRECTION)
			name = "SH_WORD SH_REDIRECTION";
	}
	else if (type == SH_PIPE)
		name = "SH_PIPE";
	else if (type == SH_REDIRECTION)
		name = "SH_REDIRECTION";
	else if (type == SH_SEMI)
		name = "SH_SEMI";
	else
		name = (char *)NULL;
	return (name);
}

void	print_tokens(t_token_list *list)
{
	t_token *current;

	current = list->head;
	while (current)
	{
		debug_msg("token is |%s| and type is |%s|\n",\
				current->token, enum_char(current->tok_type));
		current = current->next;
	}
	debug_msg("\n=========================================\n");
}
