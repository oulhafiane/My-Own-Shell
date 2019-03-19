/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:45:28 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/19 15:40:26 by amoutik          ###   ########.fr       */
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
	if ((error = full_path(&(*cmd)[0], path) == SUCCESS))
		execve((*cmd)[0], *cmd, env_tab);
	else if ((bltin = ft_lstsearch(built_in, (*cmd)[0], &check_builtin)) != NULL)
		((t_builtin*)bltin->content)->f((*cmd)[1], env);
	else if (error == EACCESS)
		ft_printf_fd(2, "%s Permission denied\n", (*cmd)[0]);
	else if (error == EFILE)
		ft_printf_fd(2, "21sh : command not found: %s\n", (*cmd)[0]);
	exit(EXIT_FAILURE);
}

void	piping(t_list *cmds, t_list **env, t_list *built_in, pid_t pid)
{
	int			p[2];
	int			fd_in;
	t_redirect	*redirect;

	fd_in = 0;
	while (cmds != NULL)
	{
		pipe(p);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			redirect = (t_redirect *)cmds->content;
			if (!loop_dup2(redirect->dup_head))
				dup2(fd_in, 0);
			else
				exit_shell("Ambiguous input redirect.\n");
			if (cmds->next != NULL)
			{
				dup2(p[1], 1);
				close(p[1]);
			}
			loop_dup(redirect->dup_head);
			close(p[0]);
			execute_command(&redirect->command, env, built_in);
		}
		else
		{
			wait(NULL);
			close(p[1]);
			fd_in = p[0];
			cmds = cmds->next;
		}
	}
}

int		is_piped(t_command_list *ptr)
{
	t_command	*current;
	int			count;

	current = ptr->head;
	count = 0;
	while (current)
	{
		if (!current->is_quoted && *current->argv == '|' && ft_strlen(current->argv) == 1)
			count++;
		current = current->next;
	}
	return (count);
}

t_list		*get_command(t_command_list *command)
{
//	char			***cmd;
//	int				i;
	t_command_list	*tmp;
	t_list			*list_commands;
	t_redirect		*redirect;

	list_commands = NULL;
//	i = 0;
/*	if ((cmd = (char ***)malloc(sizeof(char **) * (count + 2))) == NULL)
		return (NULL);
*/
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
	pid_t	pid;

	pid = 0;
	//removed count
	list = get_command(command);
	piping(list, env, built_in, pid);
	ft_lstdel(&list, &free_cmd);
	//free(cmds);
}
