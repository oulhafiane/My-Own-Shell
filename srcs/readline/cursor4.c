/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 17:39:00 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/09/21 06:44:09 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_index(t_line *line, char step)
{
	int		top;
	int		index;

	line->index += step;
	line->current_index += step;
	if (step == 1 && line->command[line->index] == '\n')
		line->current_index = -1;
	else if (step == -1 && line->command[line->index + 1] == '\n')
	{
		index = line->index;
		while (index >= 0 && line->command[index] != '\n')
			index--;
		top = -1;
		while (line->command[++index] != '\0' && line->command[index] != '\n')
			top++;
		line->current_index = top;
	}
}

int		decision_up_down(t_line *line)
{
	int		marge;

	marge = 0;
	if (line->index == line->current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	if ((line->current_index + marge + line->total_tabs) % line->col == line->col - 1)
		return (1);
	else
		return (0);
}

int		get_rows(t_line *line, int i, int j, int count_rows)
{
	int		diff;

	j += line->total_tabs;
	while (line->command[++i] != '\0')
	{
		if (line->command[i] == '\t')
		{
			diff = line->col - (j % line->col);
			if (diff > line->col % 8)
				diff = 8 - ((j % line->col) % 8);
			else
				count_rows++;
			j += diff;
		}
		else if (line->command[i] == '\n')
		{
			count_rows++;
			j = 0;
		}
		else if (j % line->col == line->col - 1)
			count_rows++;
		j++;
	}

	return (count_rows);
}

int		get_current_rows(t_line *line)
{
	int	i;
	int	j;
	int	count_rows;

	count_rows = 0;
	i = line->index;
	if (line->index == line->current_index)
		j = line->current_index + 1 + ft_strlen(GET_MSG(line->print_msg));
	else
		j = line->current_index + 1;
	return (get_rows(line, i, j, count_rows));
}

void		decision_top_down_left(t_line *line, int current_rows)
{
	int		height;
	int		i;
	//int		current_row;
	int		diff_rows;

	ft_debug("count_down : %d\n", line->count_down);
	height = tgetnum("li");
	if (line->current_row + line->count_down > height)
	{
		ft_debug("current_rows : %d\n", current_rows);
		ft_debug("current row : %d\n", get_current_row(height));
		ft_debug("height : %d\n", height);
		//if (get_current_row(height) + current_rows == height)
		//{
		diff_rows = (line->current_row + line->count_down) - height;
			i = -1;
			ft_debug("Ok gooo UP!\n");
			while (++i < diff_rows)
				tputs(tgetstr("up", NULL), 1, ft_putchar);
		//}
	}
	ft_debug("=====\n");
}

void	set_new_current_index(t_line *line)
{
	int		index;

	index = line->index - 1;
	while (index >= 0 && line->command[index] != '\n')
		index--;
	if (index > 0)
		line->current_index = line->index - index;
	else
		line->current_index = line->index;
}
