/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:34:39 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/18 22:57:55 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	before(t_line *line, int col, char mode)
{
	char	tmp;

	tmp = line->command[line->index + 1];
	line->command[line->index + 1] = '\0';
	ft_strcpy(line->copy, line->command);
	line->command[line->index + 1] = tmp;
	if (mode == MODE_CUT)
	{
		while (line->index >= 0)
			move_cursor(BACK_KEY, line, col);
	}
}

static void	after(t_line *line, char mode)
{
	ft_strcpy(line->copy, line->command + line->index + 1);
	if (mode == MODE_CUT)
	{
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		line->top = line->index;
	}
}

static void	all(t_line *line, int col, char mode)
{
	ft_strncpy(line->copy, line->command, COPY_MAX - 1);
	if (mode == MODE_CUT)
	{
		go_home(line, col);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		free_line();
		init_line();
	}
}

void		handle_copy(t_line *line, int key, int col)
{
	if (key == CTRL_K)
		after(line, MODE_CUT);
	else if (key == CTRL_U)
		before(line, col, MODE_CUT);
	else if (key == CTRL_X)
		all(line, col, MODE_CUT);
	else if (key == ALT_RIGHT)
		after(line, MODE_COPY);
	else if (key == ALT_LEFT)
		before(line, col, MODE_COPY);
	else if (key == ALT_C)
		all(line, col, MODE_COPY);
}
