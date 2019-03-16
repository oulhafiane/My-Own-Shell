/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:45:59 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/16 18:12:27 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_redirect		*init_t_redirect()
{
	t_redirect		*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	redirect->command = NULL;
	redirect->dup_head = NULL;
	redirect->dup_tail = NULL;
	return (redirect);
}

t_duped			*init_t_duped(t_redirect *redirect)
{
	t_duped		*node;

	if((node = (t_duped *)malloc(sizeof(t_duped))) == NULL)
		return (NULL);
	node->filed1 = -1;
	node->filed2 = -1;
	node->del = NULL;
	node->next = NULL;

	if (redirect->dup_head == NULL)
	{
		redirect->dup_head = node;
		redirect->dup_tail = node;
	}
	else
	{
		redirect->dup_tail->next = node;
		redirect->dup_tail = node;
	}
	return (node);
}

int				is_number(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str))
			return (0);
		str++;
	}
	return (1);
}

int				redir_out(char *filename, int perm)
{
	int		fd_out;

	fd_out = open(filename, perm | O_CREAT, 0644);
	return (fd_out);
}

void			file_or_fdes(t_command **command, t_duped *duped)
{
	if (*(++(*command)->argv))
		duped->filed1 = redir_out((*command)->argv, O_WRONLY | O_TRUNC);
	else
	{
		if(!ft_strchr((*command = (*command)->next)->argv, '>'))
			duped->filed1 = redir_out((*command)->argv, O_WRONLY | O_TRUNC);
		(*command)->is_skiped = 1;
	}

}

void		reverse_agregate(t_command **command, t_duped *duped)
{
	duped->filed2 = 1;
	if ((*command)->argv + 2 != '\0')
	{
		++(*command)->argv;
		file_or_fdes(command, duped);
	}
	else
	{
		*command = (*command)->next;;
		(*command)->is_skiped = 1;
		duped->filed1 = 2;
	}
}

/*
** Handling somthing like this ls -la > file 2>&1
** Or somthing like this [ls -la &> file | ls -la >& file]
*/

void		agregate_redirect(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;
	int			num;
	t_command	*current;

	current = *command;
	num = 0;
	current->is_skiped = 1;
	duped = init_t_duped(redirect);
	if(*current->argv && ft_isdigit(*current->argv))
	{
		duped->filed2 = *current->argv - '0';
		current->argv++;
		if (*current->argv == OUTPUT_REDI && *(++current->argv) == AMPERSAND)
		{
			if(is_number(++current->argv) && ft_isdigit(*current->argv) && *current->argv <= '2')
				duped->filed1 = *current->argv - '0';
			else if (*current->argv == '-')
				duped->filed1 = -2;
			else if (is_number(current->argv) && (num = ft_atoi(current->argv)) > 2)
				ft_printf_fd(2, "21sh : %d: Bad file descriptor\n", num);
			else
				ft_printf_fd(2, "21sh : %s: ambiguous redirect\n", current->argv);
		}
	}
	else if (strncmp(current->argv, GREATAND, 2) == 0 || strncmp(current->argv, GREATAND_R, 2) == 0)
		reverse_agregate(command, duped);
}

/*
**	This for the n>[word];
**	Or something like >[word];
*/

void			simple_redirect(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;
	int			num;

	num = 0;
	(*command)->is_skiped = 1;
	if (*(*command)->argv && (ft_isdigit(*(*command)->argv) || *(*command)->argv == OUTPUT_REDI))
		duped = init_t_duped(redirect);
	if (*(*command)->argv && ft_isdigit(*(*command)->argv))
	{
		duped->filed2 = *(*command)->argv - '0';
		(*command)->argv++;
		if (*(*command)->argv == OUTPUT_REDI)
			file_or_fdes(command, duped);
	}
	else if (*(*command)->argv && *(*command)->argv == OUTPUT_REDI)
	{
		file_or_fdes(command, duped);
		duped->filed2 = 1;
	}
}

void			double_great(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;

	(*command)->is_skiped = 1;
	duped = init_t_duped(redirect);
	if (ft_isdigit(*(*command)->argv))
	{
		duped->filed2 = *(*command)->argv - '0';
		(*command)->argv++;
	}
	else
		duped->filed2 = 1;
	if (*(*command)->argv == OUTPUT_REDI && *(++(*command)->argv) == OUTPUT_REDI)
	{	
		if (*(++(*command)->argv) != '\0')
			duped->filed1 = redir_out((*command)->argv, O_WRONLY | O_APPEND);
		else
		{
			*command = (*command)->next;
			if (*command && (*command)->argv)
			{
				duped->filed1 = redir_out((*command)->argv, O_WRONLY | O_APPEND);
				(*command)->is_skiped = 1;
			}
		}
	}
	else
		ft_printf_fd(2, "21sh : syntax error near unexpected token `%c'\n", *(*command)->argv);
}

/*
** Functions belows Handles input redirection such < <& << <<- <<<
*/

int				redir_in(char *filename, int perm)
{
	int		fd_in;

	fd_in = open(filename, perm);
	return (fd_in);
}

void			simple_in_redirect(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;

	duped = init_t_duped(redirect);
	duped->filed2 = 0;
	(*command)->is_skiped = 1;
	if (++(*command)->argv != '\0')
		duped->filed1 = redir_in((*command)->argv, O_RDONLY);
	else
	{
		*command = (*command)->next;
		(*command)->is_skiped = 1;
		duped->filed2 = redir_in((*command)->argv, O_RDONLY);
	}
}

void			jump_forward(t_command **command, t_duped *duped)
{
	*command = (*command)->next;
	(*command)->is_skiped = 1;
	duped->del = ft_strjoin((*command)->argv, "\n");
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
			duped->del = ft_strjoin((*command)->argv + 3, "\n");
		duped->filed2 = -4;
	}
	else if (ft_strncmp((*command)->argv, DLESS, 2) == 0)
	{
		if (len == 2)
			duped->del = ft_strdup((*command)->argv + 2);
		else if (*((*command)->argv + 2) == '-')
			duped->del = ft_strdup((*command)->argv + 3);
	}
}

void		less_and(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;
	t_command	*cmd;

	duped = init_t_duped(redirect);
	(*command)->is_skiped = 1;
	duped->filed2 = 0;
	if (ft_isdigit(*(*command)->argv))
	{
		duped->filed2 = *(*command)->argv - '0';
		(*command)->argv++;
	}
	if (*(*command)->argv == INPUT_REDI && *((*command)->argv + 1) == AMPERSAND)
	{
		(*command)->argv = (*command)->argv + 2;
		if (*(*command)->argv && ft_isdigit(*(*command)->argv))
			duped->filed1 = *(*command)->argv - '0';
		else if (*(*command)->argv == '-')
			duped->filed1 = -2;
		else
		{
			cmd = (*command)->next;
			ft_printf_fd(2, "21sh: %s: ambiguous redirect\n", cmd->argv);
			exit(EXIT_FAILURE);
		}
	}
}

void			parse_redirection(t_command **command, t_redirect *redirect)
{
	if (ft_strstr((*command)->argv, GREATAND) || ft_strstr((*command)->argv, GREATAND_R))
		agregate_redirect(command, redirect);
	else if (ft_strstr((*command)->argv, DGREAT))
		double_great(command, redirect);
	else if (ft_strstr((*command)->argv, "<<"))
		double_less(command, redirect);
	else if (ft_strstr((*command)->argv, LESSAND))
		less_and(command, redirect);
	else if (ft_strstr((*command)->argv, "<"))
		simple_in_redirect(command, redirect);
	else
		simple_redirect(command, redirect);
}

t_redirect		*handle_redirect(t_command_list *command)
{
	t_redirect		*redirect;
	t_command		*current;

	redirect = init_t_redirect();
	current = command->head;
	while (current)
	{
		if (!current->is_quoted && (ft_strchr(current->argv, '>') || ft_strchr(current->argv, '<')))
			parse_redirection(&current, redirect);
		current = current->next;
	}
	redirect->command = list_to_chars(command);
	return (redirect);	
}
