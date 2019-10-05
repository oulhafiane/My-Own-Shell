/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:05:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 14:51:09 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_free_array(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_setup_child(t_params *params)
{
	ft_getset(0)->list = NULL;
	ft_getset(0)->interractive = 0;
	if (params->pipe_stdin >= 0)
		close(params->pipe_stdin);
	ft_jobs_in_child();
}

void	ft_fork(t_params *params, char *file, t_command *cmd, t_builtin *blt)
{
	char	**env;
	pid_t	pid;

	env = NULL;
	if (!blt)
		env = env_to_tab(params->tmpenv ? params->tmpenv : ft_getset(0)->env);
	pid = fork();
	if (!pid)
	{
		ft_setup_child(params);
		if (blt)
			run_builtin(params, blt->f, cmd->argv, params->tokens);
		else
		{
			execve(file, cmd->argv + params->argv_index, env);
			ft_printf_fd(2, "Wrong exec format\n");
			exit(1);
		}
		exit(0);
	}
	ft_handle_jobs(params->tokens, pid);
	ft_free_array(env);
}

int		ft_error(char *error, char *name)
{
	ft_set_last_rvalue(127);
	ft_printf_fd(2, error, name);
	return (0);
}

int		ft_run(t_params *params, t_command *cmd)
{
	char	*file;
	char	*error;

	error = NULL;
	if ((file = ft_findfile(cmd->argv[params->argv_index], &error)))
		ft_fork(params, file, cmd, NULL);
	else if (!error)
		error = "42sh: %s: command not found\n";
	if (error)
		ft_error(error, cmd->argv[params->argv_index]);
	free(file);
	return (1);
}
