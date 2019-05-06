/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:45:45 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/06 20:10:55 by zoulhafi         ###   ########.fr       */
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

static void	heredoc(t_token *token, int std[2])
{
	char	*doc;
	int		pp[2];

	doc = getdoc(token);
	if (doc != NULL)
	{
		pipe(pp);
		dup2(pp[0], std[0]);
		ft_printf_fd(pp[1], "%s\n", doc);
		close(pp[1]);
	}
	free(doc);
}

static char	theredoc(t_token *token, int std[2])
{
	int		fd;
	int		pp[2];
	char	buf;

	if ((fd = open(token->token, O_RDONLY)) == -1)
		return (PERM_DENIED2);
	pipe(pp);
	dup2(pp[0], std[0]);
	while (read(fd, &buf, 1) > 0)
		write(pp[1], &buf, 1);
	close(pp[1]);
	return (0);
}

static char	handle_left_redirect(t_token *token, int std[2])
{
	t_token		*left;
	char		*file;

	while (token && !(token->tok_type & SH_SEMI) &&
			!(token->tok_type & SH_PIPE))
	{
		if ((token->tok_type & SH_REDIRECTION) && ft_strchr(token->token, '<'))
		{
			left = token;
			token->tok_type = 0;
			if (token->next)
				token->next->tok_type = 0;
		}
		token = token->next;
	}
	if (left)
	{
		file = ft_strchr(left->token, '<') + 1;
		if (*file == '\0' && left->next)
			return (theredoc(left->next, std));
		else if (*file == '<' && left->next)
			heredoc(left->next, std);
		else
			return (SYNTAX_ERROR);
	}
	return (0);
}

char	handle_redirection(t_token *token, int std[2])
{
	char	status;

	if ((status = handle_left_redirect(token, std)) != 0)
		return (status);
	if ((status = handle_right_redirect(token)) != 0)
		return (status);
	return (0);
}
