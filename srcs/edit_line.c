/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:44:17 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/20 16:14:19 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	delete_char(t_line *line)
{
	if (line->index >= 0)
		ft_memmove(line->command + line->index,
				line->command + (line->index + 1),
				line->top - line->index);
	line->command[line->top--] = 0;
}

void	add_char(t_line *line, char c)
{
	char *tmp;

	if (line->top + 2 >= line->buf_size)
		line->buf_size *= 2;
	tmp = ft_strnew(line->buf_size);
	ft_strncpy(tmp, line->command, line->index + 1);
	tmp[line->index + 1] = c;
	ft_strncpy(tmp + line->index + 2,
			line->command + line->index + 1, line->top - line->index);
	tmp[++line->top + 1] = '\0';
	free(line->command);
	line->command = tmp;
}

static void	print_newchar(t_line *line, int buf)
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
	line->command[++(line->index)] = buf;
	line->top++;
	init_terms();
	col = tgetnum("co");
	if ((line->index + ft_strlen(GET_MSG(line->print_msg))) % col == col - 1)
	{
		go_down_left();
		line->begin_row--;
	}
}

void	print_char_inline(t_line *line, int buf)
{
	if (line->index >= line->top)
		print_newchar(line, buf);
	else
		move_cursor(buf, line);
}
