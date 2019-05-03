/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:58:13 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/22 12:20:48 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		handling_parsed_line(t_command_list *command,
		char *new_line, int *i, char flag)
{
	if (flag == 1)
		add_to_list(command, ft_strndup(new_line, *i), i, 1);
	else if (flag == 2)
		push_non_quoted(new_line, i, command);
}

static char		check_tilda_dollar(char **line, char **new_line, t_spliter *spl,
		t_list *env)
{
	int flag;

	flag = 0;
	if (D_COND && handle_dollar(line, new_line, env, spl))
		return (1);
	else
	{
		if ((spl->start < *line &&
				ft_iswhitespace(*(*line - 1))) || spl->start == *line)
			flag = 1;
		if (flag &&
			!spl->spliter && **line == TILDA
			&& (*(*line + 1) == '/' || ft_iswhitespace(*(*line + 1))
				|| *(*line + 1) == '\0')
			&& handle_tilda(line, new_line, env, spl))
			return (1);
	}
	return (0);
}

static void		space_escaping(t_command_list *command,
		char **line, t_spliter *spl, char **new_line)
{
	while (**line && spl->spliter == 0 &&
			ft_strchr(" \t", **line) && (ft_strchr(" \t", *(*line + 1))))
		(*line)++;
	if (spl->spliter == 0 && spl->i == 1 && (*new_line)[0] == ' ')
		spl->i = 0;
	last_word(command, line, new_line, &(spl->i));
}

static void		init_spliter(t_spliter *spl, char *start)
{
	spl->i = 0;
	spl->start = start;
	spl->len = ft_strlen(start);
}

void			handle_quote(t_line *current,
		t_command_list *command, char flag, t_list *env)
{
	t_spliter	spl;
	char		*start;
	char		*line;
	char		*new_line;

	init_var(current, &line, &start, &(spl.spliter));
	new_line = ft_strnew(ft_strlen(line));
	init_spliter(&spl, start);
	while (*line)
	{
		flag = check_quote(&line, &(spl.spliter), start);
		if (flag == 0)
			continue ;
		else if (flag == 32)
			;
		else if (check_tilda_dollar(&line, &new_line, &spl, env) == 1)
			continue ;
		else if (flag != -1)
			handling_parsed_line(command, new_line, &(spl.i), flag);
		new_line[spl.i++] = *line++;
		space_escaping(command, &line, &spl, &new_line);
	}
	free(new_line);
	is_match(spl.spliter, current, command, start);
}
