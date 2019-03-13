/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:45:28 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/13 19:19:42 by amoutik          ###   ########.fr       */
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

void	piping(char ***cmd, t_list **env, t_list *built_in, pid_t pid)
{
	int		p[2];
	int		fd_in;

	fd_in = 0;
	while (*cmd != NULL)
	{
		pipe(p);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2(fd_in, 0);
			if (*(cmd + 1) != NULL)
			{
				dup2(p[1], 1);
				close(p[1]);
			}
			handle_redirection(&(*cmd));
			close(p[0]);
			execute_command(cmd, env, built_in);
		}
		else
		{
			wait(NULL);
			close(p[1]);
			fd_in = p[0];
			cmd++;
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

char		***get_command(t_command_list *command, int count)
{
	char			***cmd;
	int				i;
	t_command_list	*tmp;

	i = 0;
	if ((cmd = (char ***)malloc(sizeof(char **) * (count + 2))) == NULL)
		return (NULL);
	while (command->index)
	{
		tmp = separated_by_del(command, '|');
		if (tmp != NULL)
			cmd[i++] = list_to_chars(tmp);
		free_list(tmp, 1);
	}
	cmd[i] = NULL;
	return (cmd);
}

void	handle_piping(t_command_list *command, t_list **env, t_list *built_in, int count)
{
	char	***cmds;
	pid_t	pid;

	pid = 0;
	cmds = get_command(command, count);
	piping(cmds, env, built_in, pid);
	free(cmds);
}
