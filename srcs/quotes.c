/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:58:15 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/11 10:06:01 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_special(char c)
{
	char	*escapchar = " !@#$%^&*()-_+=,;.\"\n\t\v\f\r";
	if (ft_strchr(escapchar, c))
		return (1);
	return (0);
}

char	*readline(char *line)
{
	char	buf[1001];
	int		ret;

	while ((ret = read(0, buf, 100)) > 0)
	{
		buf[ret] = '\0';
		line = ft_strjoin(line, buf);
		if (ft_strchr(buf, '\n'))
			break;
	}
	return (line);
}

/*
 ** Remember to remove "getenv" function and replace it with local one
 ** There is also strndup function
 */

// see comment
int		handle_dollar(char **line, char **new_line, int *i)
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

char	*handle_quotes(char *line, char *new_line, t_command_list *commands)
{
	char	*start;
	int		flag;
	int		flag_d;
	int		i;

	flag = 0;
	flag_d = 0;
	i = 0;

	start = line;
	while (*line)
	{
		if (flag_d == 0 && *line == '\'')
		{
			if((flag ^= 1) == 0)
			{
				push(commands, ft_strndup(new_line, i));
				i = 0;
			}
		}
		if (flag == 0 && *line == '\\')
			ft_memmove(line, line + 1, ft_strlen(line));
		if (flag == 0 && *line == '\"')
		{
			if (flag_d ^= 1)
			{
				push(commands, ft_strndup(new_line, i));
				i = 0;
			}
		}
		if (flag_d == 0 && *line == '\\')
			line++;
		else if (flag_d && *line == '$' && handle_dollar(&line, &new_line, &i))
			continue;
		new_line[i++] = *line;
		line++;
	}
	push(commands, ft_strndup(new_line, i));
	if (flag || flag_d)
	{
		write(1, "> ", 2);
		line = readline(start);
		free_list(commands);
		return (handle_quotes(line, new_line, commands));
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*init_quotes(char *line)
{
	char			*new_line;
	t_command_list	commands;

	init_list(&commands);
	new_line = ft_strnew(1000);
	ft_bzero(new_line, 1000);
	line = handle_quotes(line, new_line, &commands);
	print_list(&commands);
	return (line);
}
