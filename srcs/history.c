/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:03:51 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/17 22:51:21 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	up_history(t_line *line)
{
	char	flag_tmp_history_saved;

	flag_tmp_history_saved = 0;
	if (line->index_history)
		line->index_history = line->index_history->previous ?
			line->index_history->previous : line->index_history;
	else if (*(line->tail_history))
	{
		line->index_history = *(line->tail_history);
		line->tmp_history = line->command;
		flag_tmp_history_saved = 1;
	}
	else
		return ;
	init_terms();
	go_home(line, tgetnum("co"));
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	if (!flag_tmp_history_saved)
		free_line();
	line = init_line();
	ft_strcpy(line->command, line->index_history->content);
	ft_printf(line->command);
	line->top = ft_strlen(line->command) - 1;
	line->index = ft_strlen(line->command) - 1;
}

static void	down_history(t_line *line)
{
	if (line->index_history)
		line->index_history = line->index_history->next;
	else
		return ;
	init_terms();
	go_home(line, tgetnum("co"));
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	free_line();
	line = init_line();
	if (line->index_history)
		ft_strcpy(line->command, line->index_history->content);
	else
	{
		ft_strcpy(line->command, line->tmp_history);
		free(line->tmp_history);
		line->tmp_history = NULL;
	}
	ft_printf(line->command);
	line->top = ft_strlen(line->command) - 1;
	line->index = ft_strlen(line->command) - 1;
}

void	add_history(t_line *line)
{
	t_list	**history;
	t_list	*new_history;

	history = line->tail_history;
	new_history = ft_lstnew(line->command, line->buf_size);
	ft_lstadd_end(history, new_history);
	*history = new_history;
	line->index_history = NULL;
}

void	handle_history(int buf, t_line *line)
{
	if (buf == UP_KEY)
		up_history(line);
	else if (buf == DOWN_KEY)
		down_history(line);
}
