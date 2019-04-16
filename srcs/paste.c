/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 22:57:23 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/15 18:45:27 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void	add_char(t_line *line, char c)
{
	char	*tmp;

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
	line->index++;
}

static void	get_pasted_str(t_line *line, char **str)
{
	char	buf;
	int		i;
	char	begin;

	i = -1;
	begin = 0;
	while (read(0, &buf, 1) > 0)
	{
		if (begin == 2 && buf == 'R')
			break ;
		else if (begin == 1 && buf == 91)
			begin = 2;
		else if (begin == 0 && buf == 27)
			begin = 1;
		else if (begin == 0 && (ft_isprint(buf) || buf == '\n' || buf == '\t'))
		{
			if (i + 1 >= line->buf_size)
			{
				*str = ft_realloc(str, line->buf_size, line->buf_size * 2);
				line->buf_size *= 2;
			}
			str[0][++i] = buf;
		}
	}
	str[0][++i] = '\0';
}

static void    paste_chars(int *buf, t_line *line)
{
	char	*str;
	char	*buf_c;
	int		i;
	int		j;

	str = (char*)malloc(sizeof(char) * line->buf_size);
	tputs("\E[6n", 1, ft_putchar);
	get_pasted_str(line, &str);
	buf_c = (char*)buf;
	i = -1;
	while (++i < 4 && (ft_isprint(buf_c[i]) || ft_strchr(" \t\n", (buf_c[i])) != NULL))
	{
		if (buf_c[i] == '\t')
		{
			j = -1;
			while (++j < 4)
				add_char(line, ' ');
		}
		else
			add_char(line, buf_c[i]);
	}
	i = -1;
	while (str[++i])
		add_char(line, str[i]);
	free(str);
}

void	print_pasted_chars(int *buf, t_line *line)
{
	int		col;
	int		diff;
	int		index;
	char	*tmp;

	free_next_newlines(line);
	diff = line->top - line->index;
	index = line->index;
	paste_chars(buf, line);
	line->index = index;
	tmp = ft_strdup(line->command + line->index + 1);
	init_terms();
	col = tgetnum("co");
	update_line(line, col, tmp, -1);
	free(tmp);
	while (diff-- > 0)
		go_left(line, col);
}
