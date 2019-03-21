/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 17:39:00 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/21 12:45:34 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_index(t_line *line, char step)
{
	line->index += step;
	line->current_index += step;
	if (line->command[line->index] == '\n')
		line->current_index = -1;
}

int		decision_down_left(t_line *line, int col)
{
	int		marge;

	marge = 0;
	if (line->index == line->current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	if ((line->current_index + marge) % col == col - 1)
		return (1);
	else
		return (0);
}

int		decision_top_down_left(t_line *line, int col)
{
	int		marge;
	int		top;

	marge = 0;
	top = line->current_index;
	while (line->command[top] != '\0' && line->command[top] != '\n')
		top++;
	if (line->index == line->current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	if ((top + marge) % col == col - 1)
		return (1);
	else
		return (0);
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
