/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:16:49 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/09/21 05:20:13 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_debug(char *format, ...)
{
	va_list	ap;
	int		fd;

	va_start(ap, format);
	fd = open(TTERMINAL, O_WRONLY);
	ft_vprintf(fd, format, &ap);
	close(fd);
	va_end(ap);
}
