/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:00:43 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/30 18:14:10 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_getfile(int fdout, t_redirect *io)
{
	int fd;

	if ((fd = open(io->file, io->mode, 0644)) < 0)
	{
		if (io->mode == O_RDONLY)
			ft_printf_fd(fdout, "21sh: no such file or directory: %s\n",
				io->file);
		else
			ft_printf_fd(fdout, "21sh: permission denied: %s\n",
			io->file);
		return (0);
	}
	dup2(fd, io->fd_src);
	close(fd);
	return (1);
}

int		ft_redirect(int fdout, t_list *out)
{
	t_redirect	*io;

	while (out)
	{
		io = out->content;
		if (io->ambiguous)
		{
			ft_printf_fd(fdout, "42sh: %s: ambiguous redirect\n", io->file);
			return (0);
		}
		if (io->file)
		{
			if (!ft_getfile(fdout, io))
				return (0);
		}
		else if (io->fd_dst == -2)
			close(io->fd_src);
		else if (dup2(io->fd_dst, io->fd_src) == -1)
		{
			ft_printf_fd(fdout, "21sh %d: bad file descriptor\n", io->fd_dst);
			return (0);
		}
		out = out->next;
	}
	return (1);
}
