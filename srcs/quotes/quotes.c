/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:58:15 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/22 12:14:23 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		check_pipe_ending(char *line, int len)
{
	while (len > 0 && ft_iswhitespace(line[--len]))
		;
	if (len > 0 && line[len] == '|')
		return (1);
	return (0);
}

char			*remove_new_line(char *line, int len)
{
	if (len > 0)
		line[--len] = '\0';
	return (line);
}

void			is_match(char spliter, t_line *current,
				t_command_list *command, char *start)
{
	int		flag_pip;
	int		len;

	len = ft_strlen(start);
	flag_pip = -1;
	if (spliter != 0 || (flag_pip = check_pipe_ending(start, len)))
	{
		free(current->old_command);
		if (flag_pip == 1)
			current->old_command = remove_new_line(start, len);
		else
			current->old_command = start;
		free_line();
		current = init_line();
		current->print_msg = 0;
		ft_printf(GET_MSG(current->print_msg));
		read_line(current);
		current->index_history = NULL;
		free_list(command, 0);
		handle_quote(current, command, -1, current->env);
	}
	else
		free(start);
}

int				is_not_only_spaces(char *line)
{
	while (*line)
	{
		if (*line != ' ' || *line != '\t')
			return (1);
		line++;
	}
	return (0);
}
