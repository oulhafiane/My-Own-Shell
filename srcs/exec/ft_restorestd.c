/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restorestd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:54:46 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/30 17:59:45 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_restorestd(char stdin, char stdout, char stderr)
{
	int fd;

	fd = open("/dev/tty", O_RDWR);
	if (stdout)
		dup2(fd, 1);
	if (stderr)
		dup2(fd, 2);
	if (stdin)
		dup2(fd, 0);
	if (fd != 0 && fd != 1 && fd != 2)
		close(fd);
}
