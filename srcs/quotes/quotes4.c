/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:58:13 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/20 11:04:52 by amoutik          ###   ########.fr       */
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
	if (D_COND && handle_dollar(line, new_line, &(spl->i), env))
		return (1);
	else if (TILDA_COND && handle_tilda(line, new_line, &(spl->i), env))
		return (1);
	return (0);
}

void			handle_quote(t_line *current,
		t_command_list *command, char flag, t_list *env)
{
	t_spliter	spl;
	char		*start;
	char		*line;
	char		*new_line;

	spl.i = 0;
	init_var(current, &line, &start, &(spl.spliter));
	new_line = ft_strnew(ft_strlen(line));
	while (*line)
	{
		flag = check_quote(&line, &(spl.spliter), start);
		if (flag == 0)
			continue ;
		else if (check_tilda_dollar(&line, &new_line, &spl, env) == 1)
			continue ;
		else if (flag != -1)
			handling_parsed_line(command, new_line, &(spl.i), flag);
		new_line[spl.i++] = *line++;
		while (*line && spl.spliter == 0 && CONTAIN_S)
			line++;
		last_word(command, &line, &new_line, &(spl.i));
	}
	free(new_line);
	is_match(spl.spliter, current, command, start);
}
