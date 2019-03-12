/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:58:15 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/12 18:25:10 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_special(char c)
{
	char	*escapchar = " !@#$%^&*()-_+=,;.\"\n\t\v\f\r\\";
	if (ft_strchr(escapchar, c))
		return (1);
	return (0);
}

int			handle_dollar(char **line, char **new_line, int *i)
{
	char *head;
	char *env;
	char *tmp;

	if (is_special(*((*line) + 1)))
		return (0);
	head = ++(*line);
	while (*head && !is_special(*head))
		head++;
	tmp = ft_strndup(*line, head - *line);
	if ((env = getenv(tmp)) == NULL)
		env = "";
	free(tmp);
	while (*env)
		(*new_line)[(*i)++] = *env++;
	*line = head;
	return (1);
}

char		**init_quotes(t_line *line, t_command_list *commands)
{
	char			*new_line;

	init_list(commands);
	new_line = ft_strnew(BUF_S);
	ft_bzero(new_line, BUF_S);
	handle_quote(line, new_line, commands, -1);
	print_list(commands);
	return (list_to_chars(commands));
}

void		is_match(char spliter, t_line *current, char *new_line, t_command_list *command, char *start)
{
	if (spliter != 0)
	{
		free(current->old_command);
		current->old_command = start;
		free_line();
		current = init_line();
		current->print_msg = 0;
		ft_printf(GET_MSG(current->print_msg));
		read_line(current);
		free_list(command);
		handle_quote(current, new_line, command, -1);
	}
	else
		free(start);
}

int			is_only_spaces(char *line)
{
	while (*line)
	{
		if (*line != ' ' || *line != '\t')
			return (1);
		line++;
	}
	return (0);
}
