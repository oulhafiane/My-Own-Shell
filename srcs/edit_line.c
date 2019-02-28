/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:44:17 by amoutik           #+#    #+#             */
/*   Updated: 2019/02/28 18:36:00 by zoulhafi         ###   ########.fr       */
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
