/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:45:59 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/19 12:18:21 by amoutik          ###   ########.fr       */
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

void			file_or_fdes(t_command **command, t_duped *duped, char *tmp)
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
	if (*tmp && *(++tmp))
		duped->filed1 = redir_out(tmp, perm);
	else
	{
		if(!ft_strchr((*command = (*command)->next)->argv, '>'))
			duped->filed1 = redir_out((*command)->argv, perm);
		(*command)->is_skiped = 1;
	}
}

void	redirect_err_out(t_command **command, t_redirect *redirect)
{
	t_duped *duped;
	char	*tmp;
	
	duped = init_t_duped(redirect);
	tmp = (*command)->argv;
	(*command)->is_skiped = 1;
	duped->filed2 = 1;
	file_or_fdes(command, duped, tmp);
	duped = init_t_duped(redirect);
	duped->filed2 = 2;
	duped->filed1 = 1;
}

void		reverse_agregate(t_command **command, t_duped *duped, char *tmp, t_redirect *redirect)
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
			break;
		}
		tmp++;
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
	char		*tmp;

	current = *command;
	tmp = current->argv;
	num = 0;
	current->is_skiped = 1;
	duped = init_t_duped(redirect);
	if(*tmp && ft_isdigit(*tmp) && *(tmp + 1) == OUTPUT_REDI)
	{
		duped->filed2 = *tmp - '0';
		tmp++;
		if (*tmp && *tmp == OUTPUT_REDI && *(++tmp) == AMPERSAND)
		{
			if(is_number(++tmp) && ft_isdigit(*tmp) && *tmp <= '2')
				duped->filed1 = *tmp - '0';
			else if (*tmp == '-')
				duped->filed1 = -2;
			else if (is_number(tmp) && (num = ft_atoi(tmp)) > 2)
				duped->filed1 = ft_printf_fd(2, "21sh : %d: Bad file descriptor\n", num) ? - 2 : -2;
			else
				duped->filed1 = ft_printf_fd(2, "21sh : %s: ambiguous redirect\n", tmp) ? -2 : -2;
		}
	}
	else if (*tmp && *tmp != AMPERSAND && *tmp != OUTPUT_REDI)
			reverse_agregate(command, duped, tmp, redirect);
	else if (strncmp(tmp, GREATAND, 2) == 0 || strncmp(tmp, GREATAND_R, 2) == 0)
		redirect_err_out(command, redirect);
}

/*
**	This for the n>[word];
**	Or something like >[word];
*/

void			simple_redirect(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;
	int			num;
	char		*tmp;

	num = 0;
	(*command)->is_skiped = 1;
	if (*(*command)->argv && (ft_isdigit(*(*command)->argv) || *(*command)->argv == OUTPUT_REDI))
		duped = init_t_duped(redirect);
	if (*(*command)->argv && ft_isdigit(*(*command)->argv))
	{
		duped->filed2 = *(*command)->argv - '0';
		tmp = (*command)->argv + 1;
		if (*tmp == OUTPUT_REDI)
			file_or_fdes(command, duped, tmp);
	}
	else if (*(*command)->argv && *(*command)->argv == OUTPUT_REDI)
	{
		file_or_fdes(command, duped, (*command)->argv);
		duped->filed2 = 1;
	}
}

void			double_great(t_command **command, t_redirect *redirect)
{
	t_duped		*duped;
	char		*tmp;

	(*command)->is_skiped = 1;
	duped = init_t_duped(redirect);
	tmp = (*command)->argv;
	if (ft_isdigit(*tmp))
	{
		duped->filed2 = *tmp - '0';
		tmp++;
	}
	else
		duped->filed2 = 1;
	if (*tmp && *tmp == OUTPUT_REDI && *(++tmp) == OUTPUT_REDI)
	{	
		if (*tmp && *(++tmp) != '\0' && *tmp != AMPERSAND)
			duped->filed1 = redir_out(tmp, O_WRONLY | O_APPEND);
		else if ((*command = (*command)->next) && (*command)->argv)
		{
				duped->filed1 = redir_out((*command)->argv, O_WRONLY | O_APPEND);
				(*command)->is_skiped = 1;
		}
		else
			duped->filed1 = ft_printf_fd(2, "21 sh : syntax error near unexprected token `%c'\n", *tmp) ? -4 : -4; 
	}
	else
		duped->filed1 = ft_printf_fd(2, "21sh : syntax error near unexpected token `%c'\n", *tmp) ? -4 : -4;
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
	char		*tmp;

	duped = init_t_duped(redirect);
	duped->filed2 = 0;
	(*command)->is_skiped = 1;
	tmp = (*command)->argv;
	if (*tmp && *(++tmp) != '\0')
	{
		if((duped->filed1 = redir_in(tmp, O_RDONLY)) == -1)
			ft_printf_fd(2, "21sh: %s: No such file or directory\n", tmp);
	}
	else
	{
		*command = (*command)->next;
		(*command)->is_skiped = 1;
		if((duped->filed1 = redir_in((*command)->argv, O_RDONLY)) == -1)
			ft_printf_fd(2, "21sh: %s: No such file or directory\n", (*command)->argv);
	}
}

void			jump_forward(t_command **command, t_duped *duped)
{
	*command = (*command)->next;
	(*command)->is_skiped = 1;
	duped->del = ft_strdup((*command)->argv);
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
	else if (ft_strstr((*command)->argv, LESSGREAT))
		less_great(command, redirect);
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
		if(current == NULL)
			break;
		current = current->next;
	}
	redirect->command = list_to_chars(command);
	return (redirect);
}
