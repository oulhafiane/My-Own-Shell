/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:03:54 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/05 17:08:05 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	make_dup(int fd, char fd_to_replace, t_token *token, char *file)
{
	dup2(fd, fd_to_replace);
	if (token->token[0] == '&' && token->token[1] == '>')
		dup2(fd, 2);
	else if (*file == '&' && ft_isdigit(token->next->token[0]) &&
			token->next->token[1] == '-' &&
			(fd = ft_atoi(token->next->token) != fd_to_replace))
		dup2(open("/dev/null", O_WRONLY), fd);
	token->tok_type = 0;
	token->next->tok_type = 0;
}

static int	get_fd(t_token *token, char *file)
{
	int		fd;

	fd = -2;
	if (*file == '\0')
		fd = open(token->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (*file == '>' && *(file + 1) == '\0')
		fd = open(token->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (*file == '&' && token->next->token[0] == '-')
		fd = open("/dev/null", O_WRONLY);
	return (fd);
}

static char	apply_redirection(t_token *token, char fd_to_replace)
{
	char	*file;
	int		fd;

	file = ft_strchr(token->token, '>') + 1;
	if (*file == '&' && ft_isdigit(token->next->token[0]))
	{
		fd = ft_atoi(token->next->token);
		if (fd < 0 || fd > 2)
			return (BAD_DESCRIPTOR);
	}
	else
		fd = get_fd(token, file);
	if (fd != -2 && fd != -1)
		make_dup(fd, fd_to_replace, token, file);
	else
		return (fd);
	return (0);
}

char		handle_redirection(t_token_list *tokens)
{
	t_token		*token;
	char		fd_to_rep;
	char		status;

	token = tokens->head;
	while (token)
	{
		if ((token->tok_type & SH_REDIRECTION) != 0 && token->next &&
				(token->next->tok_type & SH_REDIRECTION) == 0)
		{
			fd_to_rep = 1;
			if ((token->tok_type & SH_WORD) != 0)
				fd_to_rep = *(token->token) - '0';
			if ((status = apply_redirection(token, fd_to_rep)) != 0)
				return (status);
		}
		else if ((token->tok_type & SH_REDIRECTION) != 0)
			return (SYNTAX_ERROR);
		token = token->next;
	}
	return (0);
}
