/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 23:21:38 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/07 13:51:40 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	handle_redirection(t_token *token)
{
	char	status;

	if ((status = handle_left_redirect(token)) != 0)
		return (status);
	if ((status = handle_right_redirect(token)) != 0)
		return (status);
	return (0);
}

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

void	parse_heredoc(t_token_list *tokens)
{
	t_token		*ptr;
	t_token		*tmp_node;

	ptr = tokens->head;
	while (ptr)
	{
		if ((ptr->tok_type & SH_REDIRECTION) && ft_strstr(ptr->token, "<<")
				&& ptr->next)
		{
			tmp_node = (t_token*)ft_memalloc(sizeof(t_token));
			tmp_node->tok_type = ptr->next->tok_type;
			tmp_node->token = getdoc(ptr->next);
			tmp_node->next = ptr->next->next;
			ft_strdel(&(ptr->next->token));
			free(ptr->next);
			ptr->next = tmp_node;
		}
		ptr = ptr->next;
	}
}
