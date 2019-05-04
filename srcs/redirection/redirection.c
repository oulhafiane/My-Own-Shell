/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:03:54 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/04 16:48:40 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	apply_redirection(t_token **token, char fd_to_replace)
{
	char	*file;

/*	if (token->next && token->next->tok_type == SH_REDIRECTION)
	{
		
	}
	file = ft_strchr(token->token, '>') + 1;
	if (*file == NULL)
		file = token->next->token;
	else if (*file == '>'
	*/
	(void)file;
	(void)token;
	(void)fd_to_replace;

}

void		handle_redirection(t_token_list *tokens)
{
	t_token		*token;
	char		fd_to_rep;

	token = tokens->head;
	while (token)
	{
		if ((token->tok_type & SH_REDIRECTION) != 0)
		{
			fd_to_rep = 1;
			if ((token->tok_type & SH_WORD) != 0)
				fd_to_rep = *(token->token) - '0';
			apply_redirection(&token, fd_to_rep);
		}
		token = token->next;
	}
}
