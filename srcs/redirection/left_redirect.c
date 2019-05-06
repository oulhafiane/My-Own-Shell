/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:45:45 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/06 23:53:08 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*getdoc(t_token *token)
{
	t_line	*line;
	char	*doc;

	free_line();
	line = init_line();
	line->print_msg = 0;
	doc = NULL;
	while (read_line(line) == 0 && ft_strcmp(line->command, token->token) != 0
			&& line->command[line->index] != EOT_KEY)
	{
		if (doc != NULL)
			doc = ft_strjoin_pre_free(doc, "\n", line->command);
		else
			doc = ft_strdup(line->command);
		free_line();
		init_line();
		line->print_msg = 0;
	}
	return (doc);
}

static void	heredoc(t_token *token, int fd_to_rep)
{
	char	*doc;
	int		pp[2];

	doc = getdoc(token);
	if (doc != NULL)
	{
		pipe(pp);
		dup2(pp[0], fd_to_rep);
		ft_printf_fd(pp[1], "%s\n", doc);
		close(pp[0]);
		close(pp[1]);
	}
	free(doc);
}

static char	theredoc(t_token *token, int fd_to_rep)
{
	int		fd;
	int		pp[2];
	char	buf;

	if ((fd = open(token->token, O_RDONLY)) == -1)
		return (PERM_DENIED2);
	pipe(pp);
	dup2(pp[0], fd_to_rep);
	while (read(fd, &buf, 1) > 0)
		write(pp[1], &buf, 1);
	close(pp[0]);
	close(pp[1]);
	close(fd);
	return (0);
}

static t_token	*get_left_redirect(t_token *token)
{
	t_token		*left;
	int			tok_type;

	left = NULL;
	while (token && !(token->tok_type & SH_SEMI) &&
			!(token->tok_type & SH_PIPE))
	{
		if ((token->tok_type & SH_REDIRECTION) && ft_strchr(token->token, '<'))
		{
			left = token;
			tok_type = left->tok_type;
			token->tok_type = 0;
			if (token->next)
				token->next->tok_type = 0;
		}
		token = token->next;
	}
	left->tok_type = tok_type;
	return (left);
}

char		handle_left_redirect(t_token *token)
{
	t_token		*left;
	char		*file;
	int			fd_to_rep;

	left = get_left_redirect(token);
	if (left != NULL)
	{
		fd_to_rep = 0;
		if ((left->tok_type & SH_WORD) != 0)
			fd_to_rep = ft_atoi(left->token);
		left->tok_type = 0;
		file = ft_strchr(left->token, '<') + 1;
		if (*file == '\0' && left->next)
			return (theredoc(left->next, fd_to_rep));
		else if (*file == '<' && left->next)
			heredoc(left->next, fd_to_rep);
		else
			return (SYNTAX_ERROR);
	}
	return (0);
}
