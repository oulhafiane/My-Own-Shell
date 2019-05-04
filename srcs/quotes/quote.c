/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:03:33 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/04 10:09:39 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote.h"

int					is_special_char(char c)
{
	if (c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

static int			is_special_token(char **ptr,
					t_string *str, enum token_type *type)
{
	if (**ptr == '&' && !(*type & SH_REDIRECTION))
		return (0);
	if (str->len == 1 && ft_isdigit(*((*ptr) - 1)) &&
			!(*type & SH_REDIRECTION) && is_special_char(**ptr))
	{
		*type = (*type | SH_REDIRECTION);
		while (**ptr && is_special_char(**ptr))
			push(str, *(*ptr)++);
		while (**ptr && !ft_isspace(**ptr) && !is_special_char(**ptr))
			push(str, *(*ptr)++);
		if (**ptr && is_special_char(**ptr))
			return (0);
	}
	if (ft_strchr(SH_TOKEN, **ptr))
		return (0);
	return (1);
}

int					split_tok(t_token_list *list,
					char **ptr, t_string *str, enum token_type type)
{
	int				flag;

	flag = 0;
	while (**ptr && !ft_isspace(**ptr))
	{
		if (!is_special_token(ptr, str, &type))
			break ;
		if (**ptr == '\\')
		{
			if (*(++(*ptr)) != EOS)
				push(str, *(*ptr)++);
		}
		else if (**ptr == '\'' || **ptr == '"' || **ptr == '`')
		{
			if (split_quote(list, ptr, str, type | SH_QUOTED))
				return (0);
		}
		else if (**ptr && **ptr == '$' && handle_dollar(ptr, str))
			;
		else if (**ptr && **ptr == '~' && handle_tilda(ptr, str))
			;
		else if (**ptr && !ft_isspace(**ptr))
			push(str, *(*ptr)++);
	}
	insert_token(list, str, type);
	return (1);
}

static int			split_special(t_token_list *list,
					char **ptr, t_string *str)
{
	int	flag;

	flag = 0;
	while (**ptr == '|')
		push(str, *(*ptr)++);
	if (str->len == 1)
		return (insert_token(list, str, SH_PIPE));
	else if (str->len == 2)
		return (insert_token(list, str, SH_DPIPE));
	while (**ptr == ';')
	{
		if (++flag == 1)
			push(str, *(*ptr)++);
		else
			(*ptr)++;
	}
	if (str->len == 1)
		return (insert_token(list, str, SH_SEMI));
	while (**ptr && is_special_char(**ptr))
		push(str, *(*ptr)++);
	if (split_tok(list, ptr, str, SH_REDIRECTION))
		return (1);
	return (0);
}

static int			ret_with_str_free(t_string *str, int ret)
{
	free_string(str);
	return (ret);
}

static int			stringtok(const char *line, t_token_list *list)
{
	char		*ptr;
	t_string	str;

	ptr = (char *)line;
	str.string = NULL;
	new_string(&str);
	while (1)
	{
		if (ptr == NULL || *ptr == EOS)
			break ;
		while (ft_isspace(*ptr))
			ptr++;
		if (*ptr &&
				(*ptr == '\'' || *ptr == '"' || *ptr == '`'))
		{
			if (split_quote(list, &ptr, &str, SH_WORD | SH_QUOTED))
				return (ret_with_str_free(&str, 0));
		}
		else if (*ptr && !ft_isspace(*ptr) && !ft_strchr(SH_TOKEN, *ptr))
			split_tok(list, &ptr, &str, SH_WORD);
		else if (*ptr && ft_strchr(SH_TOKEN, *ptr))
			if (!split_special(list, &ptr, &str))
				return (ret_with_str_free(&str, 0));
	}
	return (ret_with_str_free(&str, 1));
}

t_token_list		*handle_quote(char **line)
{
	t_token_list	*list;
	char			*ptr;

	ptr = *line;
	if ((list = (t_token_list *)malloc(sizeof(t_token_list))) == NULL)
		return (NULL);
	init_token_list(list);
	while (!stringtok(ptr, list))
	{
		check_quote_ending(&ptr, 1);
		free_tokens(list);
	}
	*line = ptr;
	return (list);
}
