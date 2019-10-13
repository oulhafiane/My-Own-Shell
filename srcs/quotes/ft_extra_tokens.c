/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extra_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 00:38:54 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/20 00:41:01 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote.h"

void		ft_addsemicolon(t_token *token)
{
	t_token	*t;
	t_token *new;

	t = token->next;
	(void)t;
	new = malloc(sizeof(t_token));
	new->next = token->next;
	new->token = ft_strdup(";");
	new->tok_type = SH_SEMI;
	token->next = new;
}

char		ft_extra_token(t_token *token)
{
	if (token->tok_type == 4)
	{
		if (ft_strequ(token->token, "&"))
		{
			if (!token->next || (token->next && (token->next->tok_type & SH_SEMI
			|| token->next->tok_type & SH_WORD)))
			{
				if (token->next && !(token->next->tok_type & SH_SEMI))
					ft_addsemicolon(token);
				token->tok_type = SH_IMPER;
				return (1);
			}
		}
		else if (ft_strequ(token->token, "&&"))
		{
			if (token->next && (token->next->tok_type & SH_WORD))
			{
				token->tok_type = SH_LOGAND;
				return (1);
			}
		}
	}
	return (0);
}
