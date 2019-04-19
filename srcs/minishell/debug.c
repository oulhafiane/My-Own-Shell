/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 22:57:33 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/19 22:58:15 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	debug_msg(char *msg, ...)
{
	va_list	ap;
	int		fd;

	va_start(ap, msg);
	fd = open(TERM_TTY, O_WRONLY);
	ft_vprintf(fd, msg, &ap);
	va_end(ap);
	close(fd);
}
