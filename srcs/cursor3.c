/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:27:51 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/11 15:06:24 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	go_up(t_line *line, int col)
{
	int		i;

	if (line->index - 1 > col - (long)ft_strlen(GET_MSG(line->print_msg)))
	{
		if (line->copy_mode == 1)
		{
			i = -1;
			while (++i < col && line->index >= 0)
				go_left(line, col);
		}
		else
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			line->index -= col;
		}
	}
	else if (line->index + 1 >= col - (long)ft_strlen(GET_MSG(line->print_msg)))
		go_home(line, col);
}

void	go_down(t_line *line, int col)
{
	int		i;

	if (line->top + (long)ft_strlen(GET_MSG(line->print_msg)) + 1 >= col)
	{
		i = -1;
		while (++i < col && line->index < line->top)
			go_right(line, col);
	}
}

void	next_word(t_line *line, int col, int direction)
{
	int		ws;
	char	*str;

	str = line->command;
	ws = ft_iswhitespace(line->command[line->index + 1]);
	if (direction == GO_RIGHT)
	{
		while (!ws && line->index < line->top &&
				!ft_iswhitespace(str[line->index + 1]))
			go_right(line, col);
		while (line->index < line->top && ft_iswhitespace(str[line->index + 1]))
			go_right(line, col);
	}
	else if (direction == GO_LEFT)
	{
		if (!ws && line->index >= 0 && !ft_iswhitespace(str[line->index + 1]))
		{
			go_left(line, col);
			ws = 1;
		}
		while (ws && line->index >= 0 && ft_iswhitespace(str[line->index + 1]))
			go_left(line, col);
		while (line->index >= 0 && !ft_iswhitespace(str[line->index]))
			go_left(line, col);
	}
}
