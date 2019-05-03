/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:54:02 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/03 16:36:06 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	escape_slash(char **line, char *spliter, char *start, int *flag)
{
	if (IS_BSLASH || (*spliter != '\''
				&& **line == BACK_SLASH && *(*line + 1) == *spliter))
	{
		(*line)++;
		return (32);
	}
	if (!*spliter && ((ft_strchr(" \t\n", **line) || ft_strchr(SPECIAL, **line)
					|| (*line > start && ft_strchr(SPECIAL, *(*line - 1)))
					|| (*line > start && ft_strchr("\"\'", *(*line - 1))
						&& ft_strchr("<>", **line)))))
		*flag = 2;
	return (*flag);
}

void		add_to_list(t_command_list *command,
		char *line, int *index, int is_quoted)
{
	int i;

	i = 0;
	while (!is_quoted && line[i] && ft_iswhitespace(line[i]))
		i++;
	if (!is_quoted && ft_strlen(&line[i]) == 0)
		;
	else
		push(command, ft_strdup(&line[i]), is_quoted);
	*index = 0;
	free(line);
}

char		check_quote(char **line, char *spliter, char *start)
{
	int		flag;

	flag = -1;
	if (*spliter == 0 &&
			(!ft_strncmp(*line, "\"\"", 2) || !ft_strncmp(*line, "\'\'", 2)))
	{
		(*line) += 2;
		return (0);
	}
	if (IS_SINGLE_QUOTE || IS_DOUBLE_QUOTE)
	{
		*spliter = (*spliter == 0) ? *(*line) : 0;
		++(*line);
		if (*spliter == 0 && SPACE_OR_COMMA(line))
			return (flag = 1);
		else if (*spliter == 0 && QUOTE_S_D(line))
			return (0);
		else if (*spliter && CONTAIN_S_D(line, start))
			flag = 2;
	}
	return (escape_slash(line, spliter, start, &flag));
}

void		push_non_quoted(char *new_line, int *i, t_command_list *command)
{
	char	*tmp;

	tmp = ft_strndup(new_line, *i);
	if (tmp && is_not_only_spaces(tmp))
		add_to_list(command, tmp, i, 0);
	else
		free(tmp);
}

void		init_var(t_line *current,
		char **line, char **start, char *spliter)
{
	*spliter = 0;
	*line = current->old_command != NULL ?
		ft_strjoin(current->old_command, current->command)
		: ft_strdup(current->command);
	*start = *line;
}
