/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:10:15 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/15 18:56:52 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sig_handler(int sig)
{
	t_line	*line;

	(void)sig;
	init_terms();
	line = get_t_line();
	go_end(line, tgetnum("co"));
	ft_printf("\n");
	ft_printf(MSG);
	free_line();
	init_line();
	if (line->print_msg)
	{
		ft_strdel(&line->old_command);
		ioctl(0, TIOCSTI, RETURN_KEY);
	}
}

void		child_handler(int sig)
{
	(void)sig;
	ft_printf("\n");
}

void		signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGWINCH, clr_screen);
}

void		exit_shell(char *format, ...)
{
	va_list args;
	struct termios	*term;

	term = get_termios();
	tcsetattr(0, TCSANOW, term);
	va_start(args, format);
	ft_vprintf(2, format, &args);
	va_end(args);
	exit(-1);
}

void	syntax_error(t_duped *duped, char *format, ...)
{
	va_list	args;

	va_start(args, format);
	ft_vprintf(2, format, &args);
	va_end(args);
	duped->filed1 = -4;
}
