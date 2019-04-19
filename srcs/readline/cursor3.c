/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:27:51 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/19 22:53:40 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_steps_down(t_line *line)
{
	int		nl;

	if (line->new_lines && line->new_lines->next)
		nl = *((int*)line->new_lines->next->content);
	else if (line->new_lines == NULL && line->head_newlines)
		nl = *((int*)line->head_newlines->content);
	else
		nl = 0;
	return (nl);
}

void		go_down(t_line *line)
{
	int		index;

	index = 0;
	while (line->command[line->index + 1] != '\n' && index < line->col
			&& line->index < line->top)
	{
		go_right(line);
		index++;
	}
	if (index < line->col)
	{
		index += get_steps_down(line);
		go_right(line);
		while (index++ < line->col && line->command[line->index + 1] != '\n'
				&& line->index < line->top)
			go_right(line);
	}
}

static int	get_steps_up(t_line *line)
{
	int		nl;
	int		marge;
	int		index;
	int		current_index;

	index = line->index - 1;
	current_index = line->current_index - 1;
	marge = 0;
	if (index == current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	while (index >= 0 && line->command[index] != '\n')
	{
		if ((current_index + marge) % line->col == line->col - 1)
			return (1);
		index--;
		current_index--;
	}
	if (line->new_lines)
		nl = *((int*)line->new_lines->content);
	else
		nl = 1;
	return (nl);
}

void		go_up(t_line *line)
{
	int		i;
	int		steps;
	int		marge;
	char	decision;

	steps = line->col - get_steps_up(line);
	if (line->index == line->current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	i = -1;
	decision = 0;
	while ((++i <= steps || decision == 0) && line->index >= 0)
	{
		if (line->index >= 0 && ((line->command[line->index] == '\n') ||
				(line->current_index - 1 + marge) % line->col == line->col - 1))
			decision = 1;
		go_left(line);
	}
}

void		next_word(t_line *line, int direction)
{
	int		ws;
	char	*str;

	str = line->command;
	ws = !ft_isalnum(line->command[line->index + 1]);
	if (direction == GO_RIGHT)
	{
		while (!ws && line->index < line->top &&
				ft_isalnum(str[line->index + 1]))
			go_right(line);
		while (line->index < line->top && !ft_isalnum(str[line->index + 1]))
			go_right(line);
	}
	else if (direction == GO_LEFT)
	{
		if (!ws && line->index >= 0 && ft_isalnum(str[line->index + 1]))
		{
			go_left(line);
			ws = 1;
		}
		while (ws && line->index >= 0 && !ft_isalnum(str[line->index + 1]))
			go_left(line);
		while (line->index >= 0 && ft_isalnum(str[line->index]))
			go_left(line);
	}
}

void		update_line(t_line *line, char *tmp, char buf)
{
	int		i;
	int		index;
	int		current_index;
	int		height;

	i = -1;
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
	if (buf != 0 && decision_top_down_left(line) &&
			(get_current_row(height) + get_current_rows(line)) == height)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
}
