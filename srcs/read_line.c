/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:07:32 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/02/23 20:39:21 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	free_buffer(void)
{
	free_cmds();
	exit_shell("exit\n");
}

static void	check_keys(int buf, t_line *line)
{
	int col;

	if (buf == EOT_KEY)
		free_buffer();
	else if (buf == RIGHT_KEY || buf == LEFT_KEY || buf == BACK_KEY ||
			buf == DEL_KEY || buf == HOME_KEY || buf == END_KEY)
		move_cursor(buf, line);
	else if (ft_isprint(buf))
	{
		if (line->index >= line->top)
		{
			ft_putchar(buf);
			line->command[++(line->index)] = buf;
			line->top++;
			init_terms();
			col = tgetnum("co");
			if ((line->index + ft_strlen(MSG_PURE)) % col == col - 1)
				go_down_left();
		}
		else
			move_cursor(buf, line);
	}
}

static void	get_line(t_list **cmds)
{
	int			buf;

	buf = 0;
	while (read(0, &buf, 4) >= 0)
	{
		if (buf == RETURN_KEY)
			break;
		check_keys(buf, ((*cmds)->content));
		buf = 0;
	}
}

int			read_line(t_list **cmds)
{
	struct termios	*term;

	term = get_termios();
	if (tcgetattr(0, term) == -1)
		return (-1);
	if (init_termios(*term) == -1)
		return (-1);
	if (init_terms() == -1)
		return (-1);
	ft_printf(MSG);
	get_line(cmds);
	ft_printf("\n");
	if (tcsetattr(0, TCSANOW, term) == -1)
		return (-1);
	return (0);
}
