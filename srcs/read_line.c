/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:07:32 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/07 22:58:02 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	get_line(t_line *line)
{
	int		buf;

	buf = 0;
	while (read(0, &buf, 4) >= 0)
	{
		if (buf == RETURN_KEY)
		{
			move_cursor(END_KEY, line);
			line->command[++(line->index)] = buf;
			line->top++;
			break ;
		}
		check_keys(buf, line);
		buf = 0;
	}
	init_terms();
	go_end(line, tgetnum("co"));
}

void		check_keys(int buf, t_line *line)
{
	if (buf == EOT_KEY)
		free_buffer(line);
	else if (buf == RIGHT_KEY || buf == LEFT_KEY || buf == BACK_KEY ||
			buf == HOME_KEY || buf == END_KEY || buf == GO_UP ||
			buf == GO_DOWN || buf == GO_RIGHT || buf == GO_LEFT)
		move_cursor(buf, line);
	else if (buf == UP_KEY || buf == DOWN_KEY)
		handle_history(buf, line);
	else if (ft_isprint(buf))
		print_char_inline(line, buf);
	else if (((char*)&buf)[1] && (ft_isprint(*((char*)&buf)) || ft_strchr(" \t\n", (*((char*)&buf))) != NULL))
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
	line->tmp_history = NULL;
	get_line(line);
	free(line->tmp_history);
	ft_printf("\n");
	if (tcsetattr(0, TCSANOW, term) == -1)
		return (-1);
	return (0);
}
