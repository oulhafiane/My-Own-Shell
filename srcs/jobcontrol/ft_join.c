/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:57:24 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/17 15:58:07 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

char	*ft_join(char *f, ...)
{
	int		p[2];
	va_list	v;
	char	*line;
	char	*tmp;

	va_start(v, f);
	pipe(p);
	ft_vprintf(p[1], f, &v);
	va_end(v);
	get_next_line(p[0], &line);
	tmp = line;
	line = ft_strjoin(line, "\n");
	free(tmp);
	return (line);
}
