/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:45:56 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/20 15:01:08 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int		redir_out(char *filename, int perm)
{
	int		fd_out;

	fd_out = open(filename, perm | O_CREAT, 0644);
	return (fd_out);
}

void	file_to_des(t_command **command, t_duped *duped, char *tmp, int perm)
{
	if (perm == 0)
		perm = O_WRONLY | O_TRUNC;
	if (*tmp && *(++tmp))
		duped->filed1 = redir_out(tmp, perm);
	else
	{
		if ((*command = (*command)->next) != NULL
			&& !ft_strchr((*command)->argv, '>')
			&& ft_strlen((*command)->argv) > 0)
		{
			duped->filed1 = redir_out((*command)->argv, perm);
			(*command)->is_skiped = 1;
		}
		else
		{
			ft_printf_fd(2, "%s `newline'\n", ERROR_MSG);
			duped->filed1 = -4;
		}
	}
}

void	file_or_fdes(t_command **command, t_duped *duped, char *tmp)
{
	int perm;

	if (*tmp && *tmp == AMPERSAND)
		tmp++;
	perm = O_WRONLY | O_TRUNC;
	if (*(tmp + 1) && *tmp == OUTPUT_REDI)
	{
		tmp++;
		perm = O_WRONLY | O_APPEND;
	}
	file_to_des(command, duped, tmp, perm);
}

void	redirect_err_out(t_command **command, t_redirect *redirect)
{
	t_duped *duped;
	char	*tmp;

	duped = init_t_duped(redirect);
	tmp = (*command)->argv;
	(*command)->is_skiped = 1;
	duped->filed2 = 1;
	if (ft_strstr(tmp, "&>>"))
		file_or_fdes(command, duped, tmp);
	else
		file_to_des(command, duped, tmp + 1, 0);
	duped = init_t_duped(redirect);
	duped->filed2 = 2;
	duped->filed1 = 1;
}
