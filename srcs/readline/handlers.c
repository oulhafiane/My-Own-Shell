/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:10:15 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/06 20:23:22 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sig_handler(int sig)
{
	t_line	*line;

	(void)sig;
	line = get_t_line();
	go_end(line);
	ft_printf_fd(line->std[1], "\n");
	ft_printf_fd(line->std[1], MSG);
	free_line();
	line = init_line();
	if (line->print_msg)
		line->print_msg = 1;
}

void		child_handler(int sig)
{
	(void)sig;
	ft_printf_fd(get_t_line()->std[1], "\n");
}

void		signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGWINCH, clr_screen);
}

void		exit_shell(char *format, ...)
{
	va_list			args;
	struct termios	*term;

	tputs(tgetstr("ve", NULL), 1, my_putchar);
	term = get_termios();
	tcsetattr(0, TCSANOW, term);
	va_start(args, format);
	ft_vprintf(get_t_line()->std[2], format, &args);
	va_end(args);
	exit(-1);
}
