/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 22:52:46 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/19 22:38:43 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	debug_msg(char *msg, ...)
{
	va_list	ap;

	va_start(ap, msg);
	int fd = open(TERM_TTY, O_WRONLY);
	ft_vprintf(fd, msg, &ap);
	va_end(ap);
	close(fd);
}

int		get_current_row(int height)
{
	char	buf[8];
	int		row;
	int		step;
	int		ok;
	int		i;

	int cc = 0;
	ok = 1;
	while (ok)
	{
		tputs("\E[6n", 1, ft_putchar);
		ft_bzero(buf, sizeof(buf));
		read(0, buf, sizeof(buf));
		step = 0;
		if (!ft_isdigit(buf[2]))
			step = 1;
		row = buf[2 + step] - '0';
		i = 2;
		while (ft_isdigit(buf[++i + step]))
			row = (row * 10) + buf[i + step] - '0';
		if (row >= 0 && row <= height)
			ok = 0;
		cc++;
	}
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
