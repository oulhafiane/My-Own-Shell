/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:45:28 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/09 12:44:39 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_command(char ***cmd, t_list **env, t_list *built_in)
{
	int		error;
	char	**path;
	char	**env_tab;
	t_list	*bltin;

	env_tab = env_to_tab(*env);
	path = get_path(*env);
	if ((bltin = ft_lstsearch(built_in, (*cmd)[0], &check_builtin)))
	{
		((t_builtin*)bltin->content)->f(&(*cmd)[1], env);
		exit(EXIT_SUCCESS);
	}
	else if ((error = full_path(&(*cmd)[0], path)) == SUCCESS)
		execve((*cmd)[0], *cmd, env_tab);
	else if (error == ERROR_DIR)
		ft_printf_fd(2, "%s Is a Directory.\n", (*cmd)[0]);
	else if (error == EACCESS)
		ft_printf_fd(2, "%s Permission denied\n", (*cmd)[0]);
	else if (error == EFILE)
		ft_printf_fd(2, "21sh : %s: command not found\n", (*cmd)[0], error);
	exit(EXIT_FAILURE);
}

int		is_piped(t_command_list *ptr)
{
	t_command	*current;
	int			count;

	current = ptr->head;
	count = 0;
	while (current)
	{
		if (!current->is_quoted && *current->argv == '|'
			&& ft_strlen(current->argv) == 1)
			count++;
		current = current->next;
	}
	return (count);
}

t_list	*get_command(t_command_list *command)
{
	t_command_list	*tmp;
	t_list			*list_commands;
	t_redirect		*redirect;

	list_commands = NULL;
	while (command->index)
	{
		tmp = separated_by_del(command, '|');
		if (tmp != NULL)
		{
			redirect = handle_redirect(tmp);
			ft_lstadd_end(&list_commands, ft_lstnew(redirect, 0));
			free_list(tmp, 1);
		}
	}
	return (list_commands);
}

void	free_cmd(void *command, size_t size)
{
	(void)size;
	free_duped(command);
}

void	handle_piping(t_command_list *command, t_list **env, t_list *built_in)
{
	t_list	*list;

	list = get_command(command);
	piping(list, env, built_in);
	ft_lstdel(&list, &free_cmd);
}
