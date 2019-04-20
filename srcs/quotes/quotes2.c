/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:54:02 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/17 14:45:56 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	if (*spliter == 0 && ft_strncmp(*line, "\"\"", 2) == 0)
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
		else if (*spliter == 0 && SINGLE_OR_DOUBLE(line))
			return (0);
		else if (*spliter && CONTAIN_S_D(line, start))
			flag = 2;
	}
	if (IS_BSLASH || (**line == BACK_SLASH && *(*line + 1) == *spliter))
		(*line)++;
	if (!*spliter && ((ft_strchr(" \t", **line) || ft_strchr(SPECIAL, **line)
					|| (*line > start && ft_strchr(SPECIAL, *(*line - 1))))))
		flag = 2;
	return (flag);
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

void		last_word(t_command_list *command,
			char **line, char **new_line, int *i)
{
	char *tmp;

	if (**line == '\0' && *i > 1
			&& is_not_only_spaces((tmp = ft_strndup(*new_line, *i - 1))))
		add_to_list(command, tmp, i, 0);
}
