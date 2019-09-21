/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 15:12:12 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/09/20 01:32:22 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	this function called from exec_cmd,
**	if the file not found or it's permission is denied,
**	this function if the string error not null, the function prints
**	the string error, otherwise it prints a msg Command not found...
*/

void	print_error(char *error)
{
	if (error != NULL)
	{
		ft_printf_fd(2, error);
		free(error);
	}
}

void	run_redirection_with_errors(char *error, t_token *node, int std[2])
{
	char	status;
	int		fd_backup;

	dup2(std[0], 0);
	dup2(std[1], 1);
	fd_backup = -1;
	if ((status = handle_redirection(node, &fd_backup)) != 0)
		handle_errors(status);
	print_error(error);
	if (fd_backup != -1 && fd_backup != -3)
		close(fd_backup);
	restore_std();
	ft_set_last_rvalue(127);
}
