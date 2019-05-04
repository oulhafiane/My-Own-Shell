/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:03:54 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/05 00:22:58 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	apply_redirection(t_token *token, char fd_to_replace)
{
	char	*file;
	int		fd;

	file = ft_strchr(token->token, '>') + 1;
	if (*file == '\0')
	{
		fd = open(token->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, fd_to_replace);
		token->next->tok_type = 0;
	}
}

char		handle_redirection(t_token_list *tokens)
{
	t_token		*token;
	char		fd_to_rep;

	token = tokens->head;
	while (token)
	{
		if ((token->tok_type & SH_REDIRECTION) != 0 &&
				(ft_strchr(token->token, '&') != NULL ||
				 (token->next && !(token->next->tok_type & SH_REDIRECTION))))
		{
			fd_to_rep = 1;
			if ((token->tok_type & SH_WORD) != 0)
				fd_to_rep = *(token->token) - '0';
			apply_redirection(token, fd_to_rep);
		}
		else if ((token->tok_type & SH_REDIRECTION) != 0)
		{
			ft_printf_fd(2, "21sh: syntax error\n");
			return (-1);
		}
		token = token->next;
	}
	return (0);
}
