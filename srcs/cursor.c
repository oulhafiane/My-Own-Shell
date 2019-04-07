/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 10:37:12 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/07 22:51:02 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		go_right(t_line *line, int col)
{
	if (line->index >= line->top)
		return ;
	update_index(line, 1);
	ft_printf("%c", line->command[line->index]);
	if (line->command[line->index] != '\n' && decision_down_left(line, col))
		go_down_left();
	if (line->command[line->index] == '\n' && line->new_lines != NULL)
		line->new_lines = line->new_lines->next;
	else if (line->command[line->index] == '\n')
		line->new_lines = line->head_newlines;
}

void		go_left(t_line *line, int col)
{
	if (line->index < 0)
		return ;
	if (line->command[line->index] == '\n')
	{
		set_new_current_index(line);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		int step = *((int*)line->new_lines->content);
		if (line->index == line->current_index)
			step -= 3;
		tputs(tgoto(tgetstr("ch", NULL), 0, col - step), 1, ft_putchar);
		line->new_lines = line->new_lines->previous;
	}
	else if (decision_up_right(line, col))
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, col - 1), 1, ft_putchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	update_index(line, -1);
}

void		delete_new_line(t_line *line, int col, int step)
{
	set_new_current_index(line);
	tputs(tgetstr("up", NULL), 1, ft_putchar);
	if (line->index == line->current_index)
		step -= 3;
	tputs(tgoto(tgetstr("ch", NULL), 0, col - step), 1, ft_putchar);
}

static void	delete_current(t_line *line, int direction, int col)
{
	char	tmp;
	int		step;

	tmp = line->command[line->index];
	if (tmp == '\n')
		step = *((int*)line->new_lines->content);
	if (direction == DEL_KEY)
		line->index++;
	delete_char(line);
	if (direction == DEL_KEY)
		line->index--;
	if (direction == BACK_KEY)
	{
		if (tmp == '\n')
			delete_new_line(line, col, step);
		else if (line->command[line->index] == '\n')
		{
			tputs(tgetstr("le", NULL), 1, ft_putchar);
			update_index(line, -1);
		}
		else
			go_left(line, col);
	}
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_printf("%s", line->command + line->index + 1);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

static void	add_current(t_line *line, char buf, int col)
{
	int		rows_to_end;
	int		index;
	int		current_index;
	int		height;
	t_list		*newlines;

	rows_to_end = -1;
	add_char(line, buf);
	if (decision_top_down_left(line, col))
	{
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		index = line->index;
		current_index = line->current_index;
		newlines = line->new_lines;
		go_home(line, col);
		line->index = index;
		line->current_index = current_index;
		line->new_lines = newlines;
		height = tgetnum("li");
		rows_to_end = height - ((get_current_row(height) - 1) +  get_current_rows(line, col));
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
	}
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	ft_printf("%s", line->command + line->index + 1);
	if (rows_to_end == 0 && decision_top_down_left(line, col))
		go_down_left();
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	if (rows_to_end == 0 && decision_top_down_left(line, col))
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
	else if (direction == BACK_KEY && line->index >= 0)
		delete_current(line, direction, col);
	else if (direction == HOME_KEY)
		go_home(line, col);
	else if (direction == END_KEY)
		go_end(line, col);
	else if (direction == GO_UP)
		go_up(line, col);
	else if (direction == GO_DOWN)
		go_down(line, col);
	else if (direction == GO_LEFT || direction == GO_RIGHT)
		next_word(line, col, direction);
	else if (ft_isprint(direction) || direction == '\n')
		add_current(line, direction, col);
}
