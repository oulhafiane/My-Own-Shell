/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:57:24 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/01 16:28:27 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

char	*ft_read(int fd)
{
	char	*line;
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	while (get_next_line(fd, &line))
	{
		if (str)
		{
			tmp = ft_strjoin(str, "\n");
			free(str);
			str = ft_strjoin(tmp, line);
			free(line);
		}
		else
			str = line;
		free(tmp);
		line = NULL;
	}
	return (str);
}

char	*ft_join(char *f, ...)
{
	int		p[2];
	va_list	v;
	char	*str;

	va_start(v, f);
	pipe(p);
	ft_vprintf(p[1], f, &v);
	close(p[1]);
	va_end(v);
	str = ft_read(p[0]);
	close(p[0]);
	return (str);
}
