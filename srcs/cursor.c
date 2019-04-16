/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 10:37:12 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/15 16:26:15 by zoulhafi         ###   ########.fr       */
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

void update_line(t_line *line, int col, char *tmp, char buf)
{
	int		i;
	int		index;
	int		current_index;
	int		height;

	i = -1;
	if (buf != -1)
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	index = line->index;
	current_index = line->current_index;
	line->top = line->index;
	if (buf != 0 && buf != -1)
		print_newchar(line, buf);
	while (tmp[++i] != '\0')
		print_newchar(line, tmp[i]);
	if (buf != -1)
	{
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		line->index = index;
		line->current_index = current_index;
	}
	height = tgetnum("li");
	if (buf != 0 && decision_top_down_left(line, col) &&
			(get_current_row(height) + get_current_rows(line, col)) == height)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
}

static void	delete_current(t_line *line, int col)
{
	char	to_delete;
	char	*tmp;
	t_list	*tmp_newlines;

	to_delete = line->command[line->index];
	free_next_newlines(line);
	go_left(line, col);
	if (to_delete == '\n' && line->new_lines)
		free_next_newlines(line);
	tmp = ft_strdup(line->command + line->index + 2);
	line->command[line->top] = '\0';
	tmp_newlines = line->new_lines;
	update_line(line, col, tmp, 0);
	free(tmp);
	line->new_lines = tmp_newlines;
}

static void	add_current(t_line *line, char buf, int col)
{
	char	*tmp;
	t_list	*tmp_newlines;

	tmp_newlines = free_next_newlines(line);
	tmp = ft_strdup(line->command + line->index + 1);
	update_line(line, col, tmp, buf);
	go_right(line, col);
	free(tmp);
	line->new_lines = tmp_newlines;
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
		delete_current(line, col);
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
