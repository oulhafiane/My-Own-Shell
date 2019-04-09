/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:27:10 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/08 19:50:20 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_line	*get_t_line(void)
{
	static t_line	line;

	return (&line);
}

void	free_line(void)
{
	t_line	*line;
	t_list	*tmp;

	line = get_t_line();
	free(line->command);
	while (line->new_lines)
	{
		tmp = line->new_lines->next;
		free(line->new_lines);
		line->new_lines = tmp;
	}
	line->head_newlines = NULL;
	line->new_lines = NULL;
}

t_line	*init_line(void)
{
	t_line	*line;

	line = get_t_line();
	line->top = -1;
	line->index = -1;
	line->current_index = -1;
	line->print_msg = 1;
	if (line->buf_size < BUF_S)
		line->buf_size = BUF_S + 1;
	line->command = (char*)ft_memalloc(sizeof(char) * line->buf_size);
	return (line);
}


void	free_buffer(t_line *line)
{
	init_terms();
	go_home(line, tgetnum("co"));
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	free_line();
	exit_shell("exit\n");
}
