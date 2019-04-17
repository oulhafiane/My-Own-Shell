/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:44:17 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/17 15:22:58 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void update_newlines(t_line *line, int col)
{
	int		*diff;
	int		index;
	t_list	*new_newline;

	if (line->index == line->current_index)
		index = line->current_index + ft_strlen(GET_MSG(line->print_msg));
	else
		index = line->current_index;
	diff = (int*)malloc(sizeof(int));
	*diff = col - ((index + 1) % col);
	new_newline = ft_lstnew(diff, 0);
	if (line->new_lines == NULL)
		line->head_newlines = new_newline;
	ft_lstadd_end(&(line->new_lines), new_newline);
	line->new_lines = new_newline;
}

void	print_newchar(t_line *line, int buf)
{
	int		col;
	int		old_size;

	ft_putchar(buf);
	if (line->top + 2 >= line->buf_size)
	{
		old_size = line->buf_size;
		line->buf_size *= 2;
		line->command = ft_realloc(line->command, line->buf_size, old_size);
	}
	line->command[line->index + 1] = buf;
	col = tgetnum("co");
	if (buf == '\n')
		update_newlines(line, col);
	update_index(line, 1);
	line->top++;
	if (decision_up_down(line, col))
		go_down_left();
}

t_list	*free_next_newlines(t_line *line)

{
	t_list	*tmp;
	t_list	*tmp_next;

	tmp = NULL;
	if (line->new_lines)
	{
		tmp = line->new_lines->next;
		line->new_lines->next = NULL;
	}
	else if (line->head_newlines)
	{
		tmp = line->head_newlines;
		line->head_newlines = NULL;
	}
	while (tmp)
	{
		tmp_next = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = tmp_next;
	}
	return (line->new_lines);
}

void	print_char_inline(t_line *line, int buf)
{
	if (line->index >= line->top)
		print_newchar(line, buf);
	else
		move_cursor(buf, line, tgetnum("co"));
}

void	go_down_left(void)
{
	tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar);
}
