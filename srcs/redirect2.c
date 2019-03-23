/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 12:58:54 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/22 15:18:01 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		reverse_agregate(t_command **command, t_duped *duped,
		char *tmp, t_redirect *redirect)
{
	while (*tmp)
	{
		if (*tmp == AMPERSAND)
		{
			*tmp = '\0';
			(*command)->is_skiped = 0;
			duped->filed1 = redir_out(tmp + 2, O_WRONLY | O_TRUNC);
			duped->filed2 = 1;
			duped = init_t_duped(redirect);
			duped->filed2 = 2;
			duped->filed1 = 1;
			break ;
		}
		tmp++;
	}
}

/*
** Handling somthing like this ls -la > file 2>&1
** Or somthing like this [ls -la &> file | ls -la >& file]
*/

void		agregate_2_check(char *tmp, t_duped *duped, int num)
{
	if (is_number(++tmp) && ft_isdigit(*tmp) && *tmp <= '2')
		duped->filed1 = *tmp - '0';
	else if (*tmp == '-')
		duped->filed1 = -2;
	else if (is_number(tmp) && (num = ft_atoi(tmp)) > 2)
		syntax_error(duped, "21sh: %d: Bad file descriptor\n", num);
	else
		syntax_error(duped, "21sh: %s: ambiguous redirect\n", tmp);
}

void		agregate_redirect(t_command **command,
		t_redirect *redirect)
{
	t_duped		*duped;
	int			num;
	t_command	*current;
	char		*tmp;

	current = *command;
	tmp = current->argv;
	num = 0;
	current->is_skiped = 1;
	duped = init_t_duped(redirect);
	if (*tmp && ft_isdigit(*tmp) && *(tmp + 1) == OUTPUT_REDI)
	{
		duped->filed2 = *tmp - '0';
		tmp++;
		if (*tmp && *tmp == OUTPUT_REDI && *(++tmp) == AMPERSAND)
			agregate_2_check(tmp, duped, num);
	}
	else if (*tmp && *tmp != AMPERSAND && *tmp != OUTPUT_REDI)
		reverse_agregate(command, duped, tmp, redirect);
	else if (ft_strncmp(tmp, GREATAND, 2) == 0 || ft_strncmp(tmp, GREATAND_R, 2) == 0)
		redirect_err_out(command, redirect);
}

/*
**	This for the n>[word];
**	Or something like >[word];
*/

void		simple_redirect(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;
	char		*tmp;

	(*command)->is_skiped = 1;
	if (*(*command)->argv && (ft_isdigit(*(*command)->argv)
				|| *(*command)->argv == OUTPUT_REDI))
		duped = init_t_duped(redirect);
	if (*(*command)->argv && ft_isdigit(*(*command)->argv))
	{
		duped->filed2 = *(*command)->argv - '0';
		tmp = (*command)->argv + 1;
		if (*tmp == INPUT_REDI)
			syntax_error(duped, "%s `%c'\n", ERROR_MSG, *tmp);
		if (*tmp == OUTPUT_REDI)
			file_to_des(command, duped, tmp, 0);
	}
	else if (*(*command)->argv && *(*command)->argv == OUTPUT_REDI)
	{
		file_to_des(command, duped, (*command)->argv, 0);
		duped->filed2 = 1;
	}
}
