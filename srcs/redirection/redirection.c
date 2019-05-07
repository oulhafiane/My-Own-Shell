/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 23:21:38 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/07 18:34:06 by zoulhafi         ###   ########.fr       */
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

static void	parse_heredoc(t_token_list *tokens)
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

void	fix_nodes(t_token_list *tokens, t_token *token, t_token *previous)
{
	t_token		*tmp;

	if (previous != NULL)
		previous->next = token->next->next;
	else
		tokens->head = token->next->next;
	if (token->next && (token->next->tok_type & SH_WORD) && token->next->next &&
			(token->next->next->tok_type & SH_WORD))
	{
		tmp = token->next->next->next;
		token->next->next->next = token;
		token->next->next = tmp;
	}
	else
	{
		if (ft_strstr(token->token, ">>"))
			close(open(token->next->token, O_RDONLY | O_CREAT, 0644));
		else if (ft_strstr(token->token, ">"))
			close(open(token->next->token, O_RDONLY | O_TRUNC | O_CREAT, 0644));
		ft_strdel(&(token->next->token));
		free(token->next);
		ft_strdel(&(token->token));
		free(token);
	}
}

void	parse_nodes(t_token_list *tokens)
{
	t_token		*ptr;
	t_token		*previous;

	parse_heredoc(tokens);	
	ptr = tokens->head;
	previous = NULL;
	while (ptr)
	{
		if ((ptr->tok_type & SH_REDIRECTION) && (previous == NULL ||
					(previous->tok_type & SH_SEMI) || (previous->tok_type & SH_PIPE)))
		{
			fix_nodes(tokens, ptr, previous);
			previous = NULL;
			ptr = tokens->head;
			continue;
		}
		previous = ptr;
		ptr = ptr->next;
	}
}
