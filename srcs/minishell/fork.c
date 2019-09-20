/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 22:36:27 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/09/20 01:32:46 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		handle_errors(char status)
{
	ft_set_last_rvalue(127);
	if (status == -1)
		status = PERM_DENIED;
	else if (status == -2)
		status = SYNTAX_ERROR;
	if (status == PERM_DENIED)
		ft_printf_fd(2, "21sh: Permission denied\n");
	else if (status == PERM_DENIED2)
		ft_printf_fd(2, "21sh: Permission denied or file not found\n");
	else if (status == BAD_DESCRIPTOR)
		ft_printf_fd(2, "21sh: Bad file descriptor\n");
	else if (status == SYNTAX_ERROR)
		ft_printf_fd(2, "21sh: Ambiguous redirect\n");
}

/*
**  The Fork Function
**  it creates a copy (child process) of the current process (parent process)
**  man fork -> for more info.
**  after that there will be two processes one is parent and the other is child
**  the child executes the cmds with the environment given on the parameters
**  the parent waits the child to finish
*/

void		ft_init_fork(int *pip)
{
	signal(SIGINT, child_handler);
	dup2(pip[0], 0);
	dup2(pip[1], 1);
}

static void	ft_free(char **env_tab, char **cmds)
{
	ft_free_strtab(env_tab);
	ft_free_strtab(cmds);
}

void		forkit(char *path, t_list **env, t_token *token, int pip[2])
{
	pid_t		child;
	char		**cmds;
	char		**env_tab;
	int			status;

	ft_init_fork(pip);
	if ((status = handle_redirection(token, NULL)) != 0)
		return (handle_errors(status));
	if (ft_jobid_expansion(token))
	{
		env_tab = env_to_tab(*env);
		if (*(cmds = list_to_chars(token)) == NULL)
			return ;
		ft_getset(NULL)->last_status = 0;
		if (!(child = fork()))
		{
			ft_jobs_in_child();
			execve(path, cmds, env_tab);
			ft_printf_fd(2, "exec format error\n");
			exit(1);
		}
		ft_handle_jobs(token, child);
		ft_free(env_tab, cmds);
	}
	signals();
}
