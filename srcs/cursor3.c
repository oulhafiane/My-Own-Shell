/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:27:51 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/17 19:58:13 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_steps_down(t_line *line, int col)
{
	int		nl;
	int		marge;
	int		index;
	int		current_index;

	index = line->index + 1;
	current_index = line->current_index + 1;
	marge = 0;
	if (index == current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	while (line->command[index] != '\0' && line->command[index] != '\n')
	{
		if ((current_index + marge) % col == col - 1)
			return (1);
		index++;
		current_index++;
	}
	if (line->new_lines && line->new_lines->next)
		nl = *((int*)line->new_lines->next->content);
	else if (line->new_lines == NULL && line->head_newlines)
		nl = *((int*)line->head_newlines->content);
	else
		nl = 1;
	return (nl);
}

void	go_down(t_line *line, int col)
{
	int		i;
	int		steps;
	int		count_nl;
	int		marge;
	char	decision;

	steps = col - get_steps_down(line, col);
	if (line->index == line->current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	count_nl = 0;
	i = -1;
	debug_msg("====================\n");
	while (++i <= steps && line->index < line->top)
	{
		decision = 0;
		if ((line->command[line->index + 1] == '\n') ||
				(line->current_index + 1 + marge) % col == col - 1)
			decision = 1;
		debug_msg("col : %d\n", col);
		debug_msg("steps : %d\n", steps);
		debug_msg("current_index : %d\n", line->current_index + 1);
		debug_msg("desiction : %d\n", decision);
		if (count_nl == 1 && decision == 1)
			return ;
		else if (count_nl == 0 && decision == 1)
			count_nl++;
		go_right(line, col);
	}
	debug_msg("====================\n");
}

static int	get_steps_up(t_line *line, int col)
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
		if ((current_index + marge) % col == col - 1)
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

void	go_up(t_line *line, int col)
{
	int		i;
	int		steps;
	int		marge;
	char	decision;

	steps = col - get_steps_up(line, col);
	if (line->index == line->current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	i = -1;
	decision = 0;
	while ((++i <= steps || decision == 0) && line->index >= 0)
	{
		if (line->index >= 0 && ((line->command[line->index] == '\n') ||
				(line->current_index - 1 + marge) % col == col - 1))
			decision = 1;
		go_left(line, col);
	}
}

void	next_word(t_line *line, int col, int direction)
{
	int		ws;
	char	*str;

	str = line->command;
	ws = !ft_isalnum(line->command[line->index + 1]);
	if (direction == GO_RIGHT)
	{
		while (!ws && line->index < line->top &&
				ft_isalnum(str[line->index + 1]))
			go_right(line, col);
		while (line->index < line->top && !ft_isalnum(str[line->index + 1]))
			go_right(line, col);
	}
	else if (direction == GO_LEFT)
	{
		if (!ws && line->index >= 0 && ft_isalnum(str[line->index + 1]))
		{
			go_left(line, col);
			ws = 1;
		}
		while (ws && line->index >= 0 && !ft_isalnum(str[line->index + 1]))
			go_left(line, col);
		while (line->index >= 0 && ft_isalnum(str[line->index]))
			go_left(line, col);
	}
}
