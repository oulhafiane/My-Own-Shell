/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:54:02 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/14 14:29:07 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_to_list(t_command_list *command, char *line, int *index, int is_quoted)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == '\t' || line[i] == ' '))
		i++;
	push(command, ft_strdup(&line[i]), is_quoted);
	*index = 0;
	free(line);
}

static char	check_quote(char **line, char *spliter, char *start)
{
	int		flag;

	flag = -1;
	if (*spliter == 0 && ft_strncmp(*line, "\"\"", 2) == 0)
	{
		(*line) += 2;
		return (0);
	}
	if ((*spliter != DOUBLE_QUOTE && **line == SINGLE_QUOTE) ||
			(*spliter != SINGLE_QUOTE && **line == DOUBLE_QUOTE))
	{
		*spliter = *spliter == 0 ? **line : 0;
		++(*line);
		if (*spliter == 0 && (ft_iswhitespace(**line) || **line == '\0' || **line == ';'))
			flag = 1;
		if (*spliter == 0 && (**line == SINGLE_QUOTE || **line == DOUBLE_QUOTE))
			return (0);
	}
	if ((*spliter == 0 && **line == BACK_SLASH) || (**line == BACK_SLASH && *(*line + 1) == *spliter))
		(*line)++;
	if (*spliter == 0 && ((ft_strchr(" \t", **line) || ft_strchr(SPECIAL, **line)
			|| (*line > start && ft_strchr(SPECIAL, *(*line - 1))))))
		flag = 2;
	return (flag);
}

static void	push_non_quoted(char *new_line, int *i, t_command_list *command)
{
	char	*tmp;

	tmp = ft_strndup(new_line, *i);
	if (tmp && is_not_only_spaces(tmp))
		add_to_list(command, tmp, i, 0);
	else
		free(tmp);
}

static void	handling_parsed_line(t_command_list *command, char *new_line, int *i, char flag)
{
	if (flag == 1)
		add_to_list(command, ft_strndup(new_line, *i), i, 1);
	else if (flag == 2)
		push_non_quoted(new_line, i, command);
}

void		handle_quote(t_line *current, char *new_line, t_command_list *command, char flag)
{
	int		i;
	char	spliter;
	char	*start;
	char	*line;
	char	*tmp;

	i = 0;
	spliter = 0;
	line = current->old_command != NULL ?
		ft_strjoin(current->old_command, current->command) : ft_strdup(current->command);
	start = line;
	while (*line)
	{
		flag = check_quote(&line, &spliter, start);
		if (flag == 0)
			continue;
		else if (spliter != SINGLE_QUOTE && *line == DOLLAR_SIGN && handle_dollar(&line, &new_line, &i))
			continue;
		else
			handling_parsed_line(command, new_line, &i, flag);
		new_line[i++] = *line++;
		while (*line && spliter == 0 && ft_strchr(" \t", *line) && ft_strchr("\t ", *(line + 1)))
			line++;
		if (*line == '\0' && i > 1 && is_not_only_spaces((tmp = ft_strndup(new_line, i - 1))))
			add_to_list(command, tmp, &i, 0);
	}
	is_match(spliter, current, new_line, command, start);
}
