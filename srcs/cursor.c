/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 10:37:12 by amoutik           #+#    #+#             */
/*   Updated: 2019/02/23 18:58:10 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		go_left(t_line *line, int col)
{
	if ((line->index + ft_strlen(MSG_PURE)) % col == col - 1)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, col - 1), 1, ft_putchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	line->index--;
}

void		go_right(t_line *line, int col)
{
	line->index++;
	ft_printf("%c", line->command[line->index]);
	if ((line->index + ft_strlen(MSG_PURE) + 1) % col == 0)
		go_down_left();
}

static void	delete_current(t_line *line, int direction, int col)
{
	if (direction == DEL_KEY && line->index == -1)
		line->index++;
	delete_char(line);
	if (direction == DEL_KEY && line->index == 0)
		line->index--;
	if (direction == BACK_KEY)
		go_left(line, col);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_printf("%s", line->command + line->index + 1);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

static void	add_current(t_line *line, char buf, int col)
{
	int		rows_still;

	rows_still = 0;
	add_char(line, buf);
//	debug_msg("top : %d <--> col : %d <--> modulo : %d\n",
//			line->top + ft_strlen(MSG_PURE), col, (line->top + ft_strlen(MSG_PURE)) % col);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_printf("%s", line->command + line->index + 1);
	if ((line->top + ft_strlen(MSG_PURE)) % col == col - 1)
		go_down_left();
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	if ((line->top + ft_strlen(MSG_PURE)) % col == col - 1)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	go_right(line, col);
}


void		move_cursor(int direction, t_line *line)
{
	size_t col;

	init_terms();
	col = tgetnum("co");
	if (direction == RIGHT_KEY && line->index < line->top)
		go_right(line, col);
	else if (direction == LEFT_KEY && line->index >= 0)
		go_left(line, col);
	else if ((direction == DEL_KEY && line->index < line->top) ||
			(direction == BACK_KEY && line->index >= 0))
		delete_current(line, direction, col);
	else if (direction == HOME_KEY)
		go_home(line, col);
	else if (direction == END_KEY)
		go_end(line, col);
	else if (ft_isprint(direction))
		add_current(line, direction, col);
}
