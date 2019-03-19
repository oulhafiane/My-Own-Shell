/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 22:57:23 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/19 23:00:53 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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
		else if (begin == 0 && (ft_isprint(buf) || ft_iswhitespace(buf)))
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

void    paste_chars(int *buf, t_line *line)
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
				move_cursor(' ', line);
		}
		else
			move_cursor(buf_c[i], line);
	}
	i = -1;
	while (str[++i])
		move_cursor(str[i], line);
	free(str);
}
