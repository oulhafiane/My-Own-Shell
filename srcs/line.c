/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:27:10 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/18 12:31:27 by amoutik          ###   ########.fr       */
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

	line = get_t_line();
	free(line->command);
}

t_line	*init_line(void)
{
	t_line	*line;

	line = get_t_line();
	line->top = -1;
	line->index = -1;
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
