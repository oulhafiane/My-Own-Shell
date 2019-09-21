/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 10:37:12 by amoutik           #+#    #+#             */
/*   Updated: 2019/09/21 01:50:54 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		go_right(t_line *line)
{
	if (line->index >= line->top)
		return ;
	update_index(line, 1);
	if (line->command[line->index] != '\t')
		ft_printf("%c", line->command[line->index]);
	if (line->command[line->index] != '\n' && decision_up_down(line))
		go_down_left();
	if ((line->command[line->index] == '\n' ||
				line->command[line->index] == '\t') && line->new_lines != NULL)
		line->new_lines = line->new_lines->next;
	else if (line->command[line->index] == '\n' ||
			line->command[line->index] == '\t')
		line->new_lines = line->head_newlines;
	if (line->command[line->index] == '\t')
		print_current_tab(line);
	else if (line->command[line->index] == '\n') //to verify this one...
		line->total_tabs = get_next_tabs(line);
}

void		go_left(t_line *line)
{
	int		step;

	if (line->index < 0)
		return ;
	if (line->command[line->index] == '\n')
	{
		set_new_current_index(line);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		step = *((int*)line->new_lines->content);
		tputs(tgoto(tgetstr("ch", NULL), 0, line->col - step), 1, ft_putchar);
		line->new_lines = line->new_lines->previous;
		line->total_tabs = get_previous_tabs(line); // to verify
	}
	else if (decision_up_down(line))
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, line->col - 1), 1, ft_putchar);
	}
	else if (line->command[line->index] != '\t')
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	if (line->command[line->index] == '\t')
		move_left_tab(line);
	update_index(line, -1);
}

static void	delete_current(t_line *line, char flag)
{
	char	to_delete;
	char	*tmp;
	t_list	*tmp_newlines;

	(void)flag;
	to_delete = line->command[line->index];
	free_next_newlines(line);
	if (flag == BACK_KEY)
		go_left(line);
	if (to_delete == '\n' && line->new_lines)
		free_next_newlines(line);
	tmp = ft_strdup(line->command + line->index + 2);
	line->command[line->top] = '\0';
	tmp_newlines = line->new_lines;
	update_line(line, tmp, 0);
	free(tmp);
	line->new_lines = tmp_newlines;
}

static void	add_current(t_line *line, char buf)
{
	char	*tmp;
	t_list	*tmp_newlines;

	tmp_newlines = free_next_newlines(line);
	tmp = ft_strdup(line->command + line->index + 1);
	update_line(line, tmp, buf);
	go_right(line);
	free(tmp);
	line->new_lines = tmp_newlines;
}

void		move_cursor(int direction, t_line *line)
{
	if (direction == RIGHT_KEY && line->index < line->top)
		go_right(line);
	else if (direction == LEFT_KEY && line->index >= 0)
		go_left(line);
	else if ((direction == BACK_KEY && line->index >= 0) ||
			(direction == DEL_KEY && line->index < line->top))
		delete_current(line, direction);
	else if (direction == HOME_KEY)
		go_home(line);
	else if (direction == HOME_LINE)
		go_home_line(line);
	else if (direction == END_KEY)
		go_end(line);
	else if (direction == END_LINE)
		go_end_line(line);
	else if (direction == GO_UP)
		go_up(line);
	else if (direction == GO_DOWN)
		go_down(line);
	else if (direction == GO_LEFT || direction == GO_RIGHT)
		next_word(line, direction);
	else if (ft_isprint(direction) || direction == '\n')
		add_current(line, direction);
}
