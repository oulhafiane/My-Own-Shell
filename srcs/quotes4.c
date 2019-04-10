/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:58:13 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/10 20:03:06 by amoutik          ###   ########.fr       */
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

void			handle_quote(t_line *current,
		t_command_list *command, char flag, int i)
{
	char	spliter;
	char	*start;
	char	*line;
	char	*new_line;

	init_var(current, &line, &start, &spliter);
	new_line = ft_strnew(ft_strlen(line));
	while (*line)
	{
		flag = check_quote(&line, &spliter, start);
		if (flag == 0)
			continue;
		else if (D_COND && handle_dollar(&line, &new_line, &i))
			continue;
		else if (TILDA_COND && handle_tilda(&line, &new_line, &i))
			continue;
		else if (flag != -1)
			handling_parsed_line(command, new_line, &i, flag);
		new_line[i++] = *line++;
		while (*line && spliter == 0 && CONTAIN_S)
			line++;
		last_world(command, &line, &new_line, &i);
	}
	free(new_line);
	is_match(spliter, current, command, start);
}
