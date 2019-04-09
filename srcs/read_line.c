/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:07:32 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/09 15:57:33 by zoulhafi         ###   ########.fr       */
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

void		clr_screen(int sig)
{
	int		i;
	char	*tmp;
	t_line	*line;

	(void)sig;
	line = get_t_line();
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	if (line->print_msg)
		ft_printf(MSG);
	else
		ft_printf(MSG_QUOTE);
	line->index = -1;
	line->current_index = -1;
	line->top = -1;
	i = -1;
	tmp = ft_strdup(line->command);
	while (tmp[++i] != '\0')
		print_newchar(line, tmp[i]);
	free(tmp);
}

void		check_keys(int buf, t_line *line)
{
	if (buf == EOT_KEY)
		free_buffer(line);
	else if (buf == CLR_KEY1 || buf == CLR_KEY2)
		clr_screen(0);
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
