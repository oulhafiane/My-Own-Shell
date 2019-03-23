/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 09:39:05 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/23 12:22:31 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 ** Get the input from the strin
 */

void	redirect_in_app(char *del, int option)
{
	int		fd[2];
	t_line	*line;

	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	if (option == 0)
		ft_printf_fd(2, "> ");
	if (option == 0)
	{
		free_line();
		line = init_line();
		line->print_msg = 0;
		read_line(line);
		while (ft_strncmp(line->command, del, line->top) != 0)
		{
			ft_printf_fd(fd[1], "%s", line->command);
			ft_printf_fd(2, "> ", del);
			free_line();
			init_line();
			line->print_msg = 0;
			read_line(line);
		}
		free_line();
	}

	else if (option == 1)
		ft_printf_fd(fd[1], "%s\n", del);
	close(fd[1]);
	dup2(fd[0], 0);
}

void			less_great(t_command **command, t_redirect *redirect)
{
	char	*tmp;
	t_duped	*duped;

	tmp = (*command)->argv;
	(*command)->is_skiped = 1;
	duped = init_t_duped(redirect);
	if (*tmp && ft_isdigit(*tmp))
	{
		duped->filed2 = *tmp - 0;
		tmp++;
	}
	else if (*tmp && *tmp == INPUT_REDI)
		duped->filed2 = 0;
	if (*tmp && *tmp == INPUT_REDI)
		if (*(++tmp) && *tmp == OUTPUT_REDI)
		{
			if (*(++tmp))
				duped->filed1 = redir_out(tmp, O_RDWR);
			else
			{
				if ((*command = (*command)->next) && (*command)->argv)
				{
					(*command)->is_skiped = 1;
					duped->filed1 = redir_out((*command)->argv, O_RDWR);
				}
			}
		}
}

void		less_and(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;
	t_command	*cmd;
	char		*tmp;

	duped = init_t_duped(redirect);
	(*command)->is_skiped = 1;
	duped->filed2 = 0;
	tmp = (*command)->argv;
	if (*tmp && ft_isdigit(*tmp))
	{
		duped->filed2 = *tmp - '0';
		tmp++;
	}
	if (*tmp && *tmp == INPUT_REDI && *(tmp + 1) == AMPERSAND)
	{
		tmp = tmp + 2;
		if (*tmp && ft_isdigit(*tmp))
			duped->filed1 = *tmp - '0';
		else if (*tmp && *tmp == '-')
			duped->filed1 = -2;
		else
		{
			cmd = (*command)->next;
			ft_printf_fd(2, "21sh: %s: ambiguous redirect\n", cmd->argv);
			duped->filed1 = -1;
		}
	}
}

void			double_less(t_command **command, t_redirect *redirect)
{
	int		len;
	t_duped	*duped;

	duped = init_t_duped(redirect);
	(*command)->is_skiped = 1;
	len = ft_strlen((*command)->argv);
	duped->filed2 =  -2;
	if (len == 2 || ft_strcmp((*command)->argv, DLESSDASH) == 0)
		jump_forward(command, duped);
	else if (ft_strncmp((*command)->argv, "<<<", 3) == 0)
	{
		if (*((*command)->argv + 3) == '\0')
			jump_forward(command, duped);
		else
			duped->del = ft_strdup((*command)->argv + 3);
		duped->filed2 = -4;
	}
	else if (ft_strncmp((*command)->argv, DLESS, 2) == 0)
	{
		if (len == 2)
			duped->del = ft_strdup((*command)->argv + 2);
		else if (*((*command)->argv + 2) == '-')
			duped->del = ft_strdup((*command)->argv + 3);
		else
			duped->del = ft_strdup((*command)->argv + 2);
	}
}

void			jump_forward(t_command **command, t_duped *duped)
{
	*command = (*command)->next;
	if (*command)
		(*command)->is_skiped = 1;
	if (*command && (*command)->argv && ft_strlen((*command)->argv))
		duped->del = ft_strdup((*command)->argv);
	else
	{
		duped->filed2 = 0;
		syntax_error(duped, "%s\n", ERROR_MSG);
	}
}
