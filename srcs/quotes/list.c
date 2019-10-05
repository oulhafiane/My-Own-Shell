/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:34:02 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/11 18:57:43 by zoulhafi         ###   ########.fr       */
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

void	push_token(t_token_list *list, char *tok, enum e_token_type type)
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

char	free_token_list(t_token_list *list)
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
	return (1);
}
