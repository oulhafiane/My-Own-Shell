/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 22:52:46 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/02/23 19:13:50 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	debug_msg(char *msg, ...)
{
	va_list	ap;

	va_start(ap, msg);
	int fd = open(TERM_TTY, O_WRONLY);
	ft_vprintf(fd, msg, ap);
	va_end(ap);
	close(fd);
}

int		get_current_row(void)
{
	char	buf[8];
	int		row;

	tputs("\E[6n", 1, ft_putchar);
	read(0, buf, sizeof(buf));
	row = buf[2] - '0';
	if (ft_isdigit(buf[3]))
	{
		row *= 10;
		row += buf[3] - '0';
	}
//	debug_msg("row now : %d --> %s\n", row, buf+2);
	return (row);
}

void	go_down_left(void)
{
	tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar);
}

void	go_home(t_line *line, int col)
{
	size_t	step;

	step = line->index + 2;
	while (--step >= 1)
		go_left(line, col);
}

void	go_end(t_line *line, int col)
{
	size_t	step;

	step = (line->top - line->index) + 1;
	while (--step > 0)
		go_right(line, col);
}
