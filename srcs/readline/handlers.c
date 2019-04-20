/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:10:15 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/20 09:02:04 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sig_handler(int sig)
{
	t_line	*line;

	(void)sig;
	line = get_t_line();
	go_end(line);
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

void		test(int sig)
{
	debug_msg("i am sig : %d\n", sig);
}

void		signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGWINCH, clr_screen);

/*	signal(SIGTSTP, test);
	signal(SIGHUP, test);
	signal(SIGKILL, test);
	signal(SIGTERM, test);
	signal(SIGSTOP, test);
	signal(SIGTSTP, test);
	signal(SIGQUIT, test);
	signal(SIGILL, test);
	signal(SIGABRT, test);
	signal(SIGTRAP, test);
	signal(SIGEMT, test);
	signal(SIGFPE, test);
	signal(SIGBUS, test);
	signal(SIGSEGV, test);
	signal(SIGSYS, test);
	signal(SIGTTIN, test);
	signal(SIGTTOU, test);
	signal(SIGXCPU, test);
	signal(SIGXFSZ, test);
	signal(SIGVTALRM, test);
	signal(SIGALRM, test);
	signal(SIGPROF, test);
	signal(SIGTSTP, test);
	signal(SIGCONT, test);*/
}

void		exit_shell(char *format, ...)
{
	va_list			args;
	struct termios	*term;

	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	term = get_termios();
	tcsetattr(0, TCSANOW, term);
	va_start(args, format);
	ft_vprintf(2, format, &args);
	va_end(args);
	exit(-1);
}

void		syntax_error(t_duped *duped, char *format, ...)
{
	va_list	args;

	va_start(args, format);
	ft_vprintf(2, format, &args);
	va_end(args);
	duped->filed1 = -4;
}
