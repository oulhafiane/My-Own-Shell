/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:34:39 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/19 18:19:57 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	cut_text(t_line *line, int diff)
{
	int		i;

	line->copy_mode = 2;
	if (diff - 3 >= 0)
	{
		move_cursor(RIGHT_KEY, line);
		i = -1;
		while (++i < diff - 1)
			move_cursor(BACK_KEY, line);
	}
	else
	{
		i = -1;
		while (++i < (diff - 3) * -1)
			move_cursor(DEL_KEY, line);
	}
}

void		paste_text(t_line *line)
{
	int		i;
	int		len;

	len = ft_strlen(line->copy);
	i = -1;
	while (++i < len)
		move_cursor(line->copy[i], line);

}

void		end_copy_mode(t_line *line, int buf)
{
	int		diff;

	ft_bzero(line->copy, COPY_MAX);
	diff = (line->index + 2) - line->begin_copy;
	if (diff >= 0 && diff >= COPY_MAX)
		diff = COPY_MAX - 1;
	else if (diff < 0 && diff * -1 >= COPY_MAX)
		diff = (COPY_MAX - 1) * -1;
	if (diff >= 0)
		ft_strncpy(line->copy, line->command + line->begin_copy, diff);
	else
		ft_strncpy(line->copy, line->command + line->index + 1, (diff - 3) * -1);
	if (buf == CTRL_X)
		cut_text(line, diff);
	begin_reset_mode(line);
}

void		begin_reset_mode(t_line *line)
{
	int		index;
	int		col;

	line->copy_mode = (line->copy_mode) ? 0 : 1;
	init_terms();
	col = tgetnum("co");
	if (line->copy_mode == 0)
	{
		index = line->index;
		line->begin_copy = -1;
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		go_home(line, col);
		ft_printf(line->command);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		line->index = index;
	}
	else
		line->begin_copy = line->index;
}

void		go_left_copy_mode(t_line *line, int col)
{
	if (line->copy_mode == 1)
	{
		if (line->index <= line->begin_copy)
			line->copy_mode = 2;
		else
			line->copy_mode = 0;
		if (line->index == line->top)
		{
			go_left(line, col);
			go_right(line, col);
		}
		else
		{
			go_right(line, col);
			go_left(line, col);
		}
		line->copy_mode = 1;
	}
}
