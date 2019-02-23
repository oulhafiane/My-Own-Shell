/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 10:37:12 by amoutik           #+#    #+#             */
/*   Updated: 2019/02/23 20:50:44 by zoulhafi         ###   ########.fr       */
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
	int		rows_to_end;
	int		index;
	int		height;

	rows_to_end = -1;
	add_char(line, buf);
//	debug_msg("top : %d <--> col : %d <--> modulo : %d\n ===> row_to_end : %d <===== count_rows : %d\n",
//			line->top + ft_strlen(MSG_PURE), col, (line->top + ft_strlen(MSG_PURE)) % col, rows_to_end, tgetnum("li"));
	if ((line->top + ft_strlen(MSG_PURE)) % col == col - 1)
	{
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		index = line->index;
		go_home(line, col);
		line->index = index;
		height = tgetnum("li");
		rows_to_end = height - get_current_row(height) - (line->top / col);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
	}
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_printf("%s", line->command + line->index + 1);
	if (rows_to_end == 0 && (line->top + ft_strlen(MSG_PURE)) % col == col - 1)
		go_down_left();
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	if (rows_to_end == 0 && (line->top + ft_strlen(MSG_PURE)) % col == col - 1)
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
