/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:44:17 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/16 15:36:41 by zoulhafi         ###   ########.fr       */
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

	tmp = ft_strnew(BUF_S);
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

	ft_putchar(buf);
	line->command[++(line->index)] = buf;
	line->top++;
	init_terms();
	col = tgetnum("co");
	if ((line->index + ft_strlen(GET_MSG(line->print_msg))) % col == col - 1)
		go_down_left();
}

void	print_char_inline(t_line *line, int buf)
{
	if (line->index >= line->top)
		print_newchar(line, buf);
	else
		move_cursor(buf, line);
}

void	paste_chars(int *buf, t_line *line)
{
	char	*buf_c;
	int		i;
	int		j;

	buf_c = (char*)buf;
	i = -1;
	while (++i < 4 && (ft_isprint(buf_c[i]) || ft_strchr(" \t\n", (buf_c[i])) != NULL))
	{
		if (buf_c[i] == '\t')
		{
			j = -1;
			while (++j < 4)
				move_cursor(' ', line);
		}
		else
			move_cursor(buf_c[i], line);
	}
}
