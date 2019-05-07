/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:32:37 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/07 14:33:11 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	check_pipe(t_token *token)
{
	while (token)
	{
		if (token->tok_type & SH_PIPE)
			return (1);
		if (token->tok_type & SH_SEMI)
			return (0);
		token = token->next;
	}
	return (0);
}

void	next_pipe(t_token_list *tokens)
{
	t_token		*token;

	token = tokens->head;
	while (token)
	{
		if ((token->tok_type & SH_PIPE) || (token->tok_type & SH_SEMI))
		{
			tokens->head = token->next;
			return ;
		}
		token = token->next;
	}
}
