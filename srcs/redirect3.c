/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:45:59 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/20 17:47:04 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		double_great(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;
	char		*tmp;

	(*command)->is_skiped = 1;
	duped = init_t_duped(redirect);
	tmp = (*command)->argv;
	duped->filed2 = 1;
	if (ft_isdigit(*tmp) && *(tmp++))
		duped->filed2 = *(tmp - 1) - '0';
	if (*tmp && *tmp == OUTPUT_REDI && *(++tmp) == OUTPUT_REDI)
	{
		if (*tmp && *(++tmp) != '\0' &&
			*tmp != AMPERSAND && *tmp != OUTPUT_REDI)
			duped->filed1 = redir_out(tmp, O_WRONLY | O_APPEND);
		else if (*tmp != OUTPUT_REDI &&
			(*command = (*command)->next) && (*command)->argv)
		{
			duped->filed1 = redir_out((*command)->argv, O_WRONLY | O_APPEND);
			(*command)->is_skiped = 1;
		}
		else
			syntax_error(duped, "%s `%c'\n", ERROR_MSG, *tmp);
	}
	else
		syntax_error(duped, "%s `%c'\n", ERROR_MSG, *tmp);
}

/*
** Functions belows Handles input redirection such < <& << <<- <<<
*/

int			redir_in(char *filename, int perm)
{
	int		fd_in;

	fd_in = open(filename, perm);
	return (fd_in);
}

void		simple_in_redirect(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;
	char		*tmp;

	duped = init_t_duped(redirect);
	duped->filed2 = 0;
	(*command)->is_skiped = 1;
	tmp = (*command)->argv;
	if (*tmp && *(++tmp) != '\0')
	{
		if (*tmp == INPUT_REDI)
			syntax_error(duped, "%s `%c'\n", ERROR_MSG, *tmp);
		else if ((duped->filed1 = redir_in(tmp, O_RDONLY)) == -1)
			syntax_error(duped, "21sh: %s: %s \n", (*command)->argv, FN_EXIST);
	}
	else
	{
		*command = (*command)->next;
		(*command)->is_skiped = 1;
		if ((duped->filed1 = redir_in((*command)->argv, O_RDONLY)) == -1)
			syntax_error(duped, "21sh: %s: %s \n", (*command)->argv, FN_EXIST);
	}
}

void		parse_redirection(t_command **command, t_redirect *redirect)
{
	if (ft_strstr((*command)->argv, GREATAND)
			|| ft_strstr((*command)->argv, GREATAND_R))
		agregate_redirect(command, redirect);
	else if (ft_strstr((*command)->argv, DGREAT))
		double_great(command, redirect);
	else if (ft_strstr((*command)->argv, "<<"))
		double_less(command, redirect);
	else if (ft_strstr((*command)->argv, LESSAND))
		less_and(command, redirect);
	else if (ft_strstr((*command)->argv, LESSGREAT))
		less_great(command, redirect);
	else if (ft_strstr((*command)->argv, "<"))
		simple_in_redirect(command, redirect);
	else
		simple_redirect(command, redirect);
}

t_redirect	*handle_redirect(t_command_list *command)
{
	t_redirect		*redirect;
	t_command		*current;

	redirect = init_t_redirect();
	current = command->head;
	while (current)
	{
		if (!current->is_quoted && (ft_strchr(current->argv, '>')
			|| ft_strchr(current->argv, '<')))
			parse_redirection(&current, redirect);
		if (current == NULL)
			break ;
		current = current->next;
	}
	redirect->command = list_to_chars(command);
	return (redirect);
}
