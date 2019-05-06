/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:03:54 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/06 23:44:59 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	make_dup(int fd, char fd_to_replace, t_token *token, char *file)
{
	char status;

	if ((status = dup2(fd, fd_to_replace)) == -1)
		return (BAD_DESCRIPTOR);
	if (token->token[0] == '&' && token->token[1] == '>')
		dup2(fd, 2);
	else if (*file == '&' && ft_isdigit(token->next->token[0]) &&
			token->next->token[1] == '-' &&
			(fd = ft_atoi(token->next->token) != fd_to_replace))
		dup2(open("/dev/null", O_WRONLY), fd);
	token->tok_type = 0;
	token->next->tok_type = 0;
	return (0);
}

static int	get_fd(t_token *token, char *file)
{
	int		fd;

	fd = -2;
	if (*file == '&' && ft_isdigit(token->next->token[0]))
		fd = ft_atoi(token->next->token);
	else if (*file == '\0')
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
	fd = get_fd(token, file);
	if (fd != -2 && fd != -1)
		return (make_dup(fd, fd_to_replace, token, file));
	else
		return (fd);
	return (0);
}

char		handle_right_redirect(t_token *token)
{
	char		fd_to_rep;
	char		status;

	while (token && (token->tok_type & SH_PIPE) == 0 &&
			(token->tok_type & SH_SEMI) == 0)
	{
		if ((token->tok_type & SH_REDIRECTION) != 0 && token->next)
		{
			fd_to_rep = 1;
			if ((token->tok_type & SH_WORD) != 0)
				fd_to_rep = ft_atoi(token->token);
			if ((status = apply_redirection(token, fd_to_rep)) != 0)
				return (status);
		}
		else if ((token->tok_type & SH_REDIRECTION) != 0)
			return (SYNTAX_ERROR);
		token = token->next;
	}
	return (0);
}
