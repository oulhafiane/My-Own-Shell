/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertalias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 14:46:11 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 14:46:20 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_insert(t_token *token, t_token *prev,
					t_token_list *tokens, t_token *new)
{
	t_token *tmp;

	if (!prev)
	{
		tmp = new;
		while (new->next)
			new = new->next;
		new->next = tokens->head->next;
		tokens->head = tmp;
		tmp = tokens->head;
	}
	else
	{
		prev->next = new;
		while (new->next)
			new = new->next;
		new->next = token->next;
	}
	free(token);
}

void	ft_insert_at(t_token_list *tokens, t_token *new, int index)
{
	t_token *token;
	t_token *prev;
	int		i;

	token = tokens->head;
	i = 0;
	prev = NULL;
	while (token)
	{
		if (i == index)
		{
			ft_insert(token, prev, tokens, new);
			break ;
		}
		i++;
		prev = token;
		token = token->next;
	}
}
