/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:07:32 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/15 20:33:52 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	print_newchar(t_line *line, int buf)
{
	int col;

	ft_putchar(buf);
	line->command[++(line->index)] = buf;
	line->top++;
	init_terms();
	col = tgetnum("co");
	if ((line->index + ft_strlen(GET_MSG(line->print_msg))) % col == col - 1)
		go_down_left();
}

static void	get_line(t_line *line)
{
	int		buf;

	buf = 0;
	while (read(0, &buf, 4) >= 0)
	{
		if (buf == RETURN_KEY)
		{
			line->command[++(line->index)] = buf;
			line->top++;
			break;
		}
		check_keys(buf, line);
		buf = 0;
	}
	init_terms();
	go_end(line, tgetnum("co"));
}

void	check_keys(int buf, t_line *line)
{
	if (buf == EOT_KEY)
		free_buffer(line);
	else if (buf == RIGHT_KEY || buf == LEFT_KEY || buf == BACK_KEY ||
			buf == DEL_KEY || buf == HOME_KEY || buf == END_KEY ||
			buf == GO_UP || buf == GO_DOWN || buf == GO_RIGHT ||
			buf == GO_LEFT || buf == UP_KEY || buf == DOWN_KEY)
		move_cursor(buf, line);
	else if (buf == TAB_KEY)
		handle_tab(line);
	else if (buf == CTRL_SPACE || buf == ESC_KEY)
		begin_reset_mode(line);
	else if (line->copy_mode == 1 && (buf == CTRL_X || buf == CTRL_C))
		end_copy_mode(line, buf);
	else if (line->copy_mode == 0 && buf == CTRL_V)
		paste_text(line);
	else if (ft_isprint(buf) || ft_iswhitespace(buf))
	{
		if (line->index >= line->top)
			print_newchar(line, buf);
		else
			move_cursor(buf, line);
	}
	else if (ft_isprint(*((char*)&buf)) || ft_iswhitespace(*((char*)&buf)))
		paste_chars(&buf, line);
}

int			read_line(t_line *line)
{
	struct termios	*term;

	term = get_termios();
	if (tcgetattr(0, term) == -1)
		return (-1);
	if (init_termios(*term) == -1)
		return (-1);
	if (init_terms() == -1)
		return (-1);
	if (line->print_msg)
		ft_printf(MSG);
	get_line(line);
	ft_printf("\n");
	if (tcsetattr(0, TCSANOW, term) == -1)
		return (-1);
	return (0);
}
