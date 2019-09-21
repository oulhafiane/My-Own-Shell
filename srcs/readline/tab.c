/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 21:38:19 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/09/21 06:05:35 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_next_tabs(t_line *line)
{
	int		i;
	int		total;
	t_list	*new_line;

	new_line = line->new_lines;
	total = 0;
	i = line->index - 1;
	while (line->command[++i] != '\n' && line->command[i] != '\0')
	{
		if (line->command[i] == '\t')
		{
			if (new_line == NULL)
				new_line = line->head_newlines;
			total += (*((int*)new_line->content) - 1);
			new_line = new_line->next;
		}
	}
	return (total);
}

int			get_previous_tabs(t_line *line)
{
	int		i;
	int		total;
	t_list	*new_line;

	new_line = line->new_lines;
	if (new_line == NULL)
		return (0);
	total = 0;
	i = line->index - line->current_index - 1;
	while (++i < line->index)
	{
		if (line->command[i] == '\t')
		{
			total += (*((int*)new_line->content) - 1);
			new_line = new_line->previous;
			if (new_line == NULL)
				return (total);
		}
	}
	return (total);
}

void		move_left_tab(t_line *line)
{
	int		step;
	int		decision;

	step = *((int*)line->new_lines->content);
	if ((decision = decision_up_down(line)))
		step--;
	if (step != 0)
		tputs(tgoto(tgetstr("LE", NULL), 0, step), 1, ft_putchar);
	line->new_lines = line->new_lines->previous;
	if (decision)
		step++;
	line->total_tabs -= (step - 1);
}

void		print_current_tab(t_line *line)
{
	int		i;
	int		step;
	int		decision;

	step = *((int*)line->new_lines->content);
	if ((decision = decision_up_down(line)))
		step--;
	i = -1;
	while (++i < step)
		ft_putchar(' ');
	if (decision)
		step++;
	line->total_tabs += (step - 1);
}

void		add_tab(t_line *line)
{
	int		*diff;
	int		index;
	t_list	*new_newline;
	int		i;

	if (line->index == line->current_index)
		index = line->current_index + ft_strlen(GET_MSG(line->print_msg));
	else
		index = line->current_index;
	index += line->total_tabs;
	diff = (int*)malloc(sizeof(int));
	*diff = line->col - ((index + 1) % line->col);
	if (*diff > line->col % 8)
		*diff = 8 - (((index + 1) % line->col) % 8);
	i = -1;
	while (++i < *diff)
		ft_putchar(' ');
	new_newline = ft_lstnew(diff, 0);
	if (line->new_lines == NULL)
		line->head_newlines = new_newline;
	ft_lstadd_end(&(line->new_lines), new_newline);
	line->new_lines = new_newline;
	line->total_tabs += (*diff - 1);
}

