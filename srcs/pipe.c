/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:45:28 by amoutik           #+#    #+#             */
/*   Updated: 2019/02/26 18:16:28 by amoutik          ###   ########.fr       */
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
		ft_printf_fd(2, "%s: command not found: %s\n", __FILE__, (*cmd)[0]);
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

int		is_piped(char **commands)
{
	int i;

	i = 0;
	while (*commands != NULL)
	{
		if (ft_strcmp(*commands, "|") == 0)
			i++;
		commands++;
	}
	return (i);
}

char	***get_commands(char **commands, int count)
{
	char	***cmd;
	char	**head;
	int		i;

	head = NULL;
	i = 0;
	if ((cmd = (char ***)malloc(sizeof(char **) * (count + 2))) == NULL)
		return (NULL);
	while (*commands != NULL)
	{
		if (head == NULL)
		{
			head = commands;
			cmd[i++] = commands;
		}
		if (ft_strcmp(*commands, "|") == 0)
		{
			*commands = NULL;
			head = NULL;
		}
		commands++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	handle_piping(char **commands, t_list **env, t_list *built_in, int count)
{
	char	***cmds;
	pid_t	pid;

	pid = 0;
	cmds = get_commands(commands, count);
	piping(cmds, env, built_in, pid);
	free(cmds);
}
