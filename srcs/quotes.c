/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:58:15 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/18 13:02:27 by amoutik          ###   ########.fr       */
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

t_command_list	*init_quotes(t_line *line, t_command_list *commands)
{
	init_list(commands);
	handle_quote(line, commands, -1);
	return (commands);
}

int			check_pipe_ending(char *line, int len)
{
	while (len > 0 && ft_iswhitespace(line[--len]))
		;
	if (len > 0 && line[len] == '|')
		return (1);
	return (0);
}

char		*remove_new_line(char *line, int len)
{
	line[--len] = '\0';
	return (line);
}

void		is_match(char spliter, t_line *current, t_command_list *command, char *start)
{
	int		flag_pip;
	int		len;

	len = ft_strlen(start);
	flag_pip = -1;
	if (spliter != 0 || (flag_pip = check_pipe_ending(start, len)))
	{
		free(current->old_command);
		current->old_command = flag_pip == 1 ? remove_new_line(start, len) : start;
		free_line();
		current = init_line();
		current->print_msg = 0;
		ft_printf(GET_MSG(current->print_msg));
		read_line(current);
		free_list(command, 0);
		handle_quote(current, command, -1);
	}
	else
		free(start);
}

int			is_not_only_spaces(char *line)
{
	while (*line)
	{
		if (*line != ' ' || *line != '\t')
			return (1);
		line++;
	}
	return (0);
}
