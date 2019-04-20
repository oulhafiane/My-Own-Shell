/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:07:32 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/20 09:02:32 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	check_keys(int buf, t_line *line)
{
	if (buf == EOT_KEY)
		handle_eot(line);
	else if (buf == CLR_KEY)
		clr_screen(0);
	else if (buf == RIGHT_KEY || buf == LEFT_KEY || buf == BACK_KEY ||
			buf == HOME_KEY || buf == END_KEY || buf == GO_UP ||
			buf == GO_DOWN || buf == GO_RIGHT || buf == GO_LEFT ||
			buf == HOME_LINE || buf == END_LINE)
		move_cursor(buf, line);
	else if (buf == ALT_LEFT || buf == ALT_RIGHT || buf == ALT_C ||
			buf == CTRL_K || buf == CTRL_U || buf == CTRL_X)
		handle_copy(line, buf);
	else if (buf == CTRL_V && ft_strlen(line->copy) > 0)
		internal_paste(line);
	else if (buf == UP_KEY || buf == DOWN_KEY)
		handle_history(buf, line);
	else if (ft_isprint(buf))
		print_char_inline(line, buf);
	else if (((char*)&buf)[1] && (ft_isprint(*((char*)&buf)) ||
				(*((char*)&buf)) == '\t' || (*((char*)&buf)) == '\n'))
		print_pasted_chars(&buf, line);
}

static void	get_line(t_line *line)
{
	int		buf;

	buf = 0;
	init_terms();
	line->col = tgetnum("co");
	while (read(0, &buf, 4) >= 0)
	{
		if (buf == RETURN_KEY)
		{
			go_end(line);
			line->command[++(line->index)] = buf;
			line->top++;
			break ;
		}
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
		check_keys(buf, line);
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		buf = 0;
	}
	go_end(line);
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
	init_terms();
	line->col = tgetnum("co");
	i = -1;
	tmp = ft_strdup(line->command);
	while (tmp[++i] != '\0')
		print_newchar(line, tmp[i]);
	free(tmp);
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
