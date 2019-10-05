/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 19:08:07 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/01 15:57:59 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		check_and_or(t_token *token)
{
	while (token)
	{
		if (token->tok_type & SH_SEMI)
			return (0);
		if (token->tok_type == SH_DPIPE)
			return (SH_DPIPE);
		if (token->tok_type & SH_LOGAND)
			return (SH_LOGAND);
		token = token->next;
	}
	return (0);
}

void	next_and_or(t_token_list *tokens)
{
	t_token		*token;

	token = tokens->head;
	while (token)
	{
		if ((token->tok_type & SH_DPIPE) ||
			(token->tok_type & SH_SEMI) || token->tok_type & SH_LOGAND)
		{
			tokens->head = token->next;
			return ;
		}
		token = token->next;
	}
}

void	ft_runnext(t_token_list *tokens, int status)
{
	int			and_or;
	t_container	*container;

	container = ft_getset(NULL);
	if (!tokens)
		return ;
	while ((and_or = check_and_or(tokens->head)))
	{
		next_and_or(tokens);
		if (((and_or & SH_DPIPE) && status)
			|| ((and_or & SH_LOGAND) && !status))
		{
			shell(container->builtins, &container->line->env, tokens);
			break ;
		}
	}
}
