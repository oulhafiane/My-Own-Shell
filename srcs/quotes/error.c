/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:23:52 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/07 09:13:24 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote.h"

int	parse_error(char *ptr)
{
	ft_printf_fd(2, "21sh: parse error near %s\n", ptr != NULL ? ptr : "\\n");
	return (1);
}

int	redirection_error2(t_token *token, char **ptr)
{
	if (**ptr != EOS)
		return (parse_error(*ptr));
	else if (!token->next)
		return (parse_error(NULL));
	else if (token->next->tok_type & SH_REDIRECTION)
		return (parse_error(token->next->token));
	else if (!(token->next->tok_type & SH_QUOTED) &&
		(ft_strchr(*ptr, '<') || ft_strchr(*ptr, '>')))
		return (parse_error(token->next->token));
	return (0);
}

int	redirection_error(t_token *token, char *ptr)
{
	int		flag;
	int		and;
	int		c;

	flag = 0;
	and = 0;
	if (ft_isdigit(*ptr) || (*ptr == '&' && ++and))
		ptr++;
	c = *ptr;
	if (*ptr == '>' || *ptr == '<')
	{
		while (*ptr == c && ++flag)
		{
			if (flag > 2)
				break ;
			ptr++;
		}
		if (and && (flag > 2 || *ptr != EOS))
			return (parse_error(ptr));
		else if (flag >= 2 && *ptr != EOS)
			return (parse_error(ptr));
		if (!and && *ptr == '&')
			ptr++;
		return (redirection_error2(token, &ptr));
	}
	return (0);
}

int	check_syntax_error(t_token_list *tokens)
{
	t_token *current;

	current = tokens->head;
	while (current)
	{
		if (current->tok_type & SH_REDIRECTION)
			if (redirection_error(current, current->token))
			{
				free_token_list(tokens);
				return (1);
			}
		current = current->next;
	}
	return (0);
}

/*
** Here we check if our line command end in proper way or not
*/

int	check_error(t_token_list *tokens)
{
	if (tokens->tail == NULL)
		return (0);
	if (tokens->tail->tok_type & SH_PIPE
			|| tokens->tail->tok_type & SH_DPIPE)
		return (1);
	return (0);
}
