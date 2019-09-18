/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:26:47 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/18 15:32:59 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_directory(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (M_ISDIR(statbuf.st_mode));
}

char	*ft_handle_errors(t_token *cmd, char *full_path)
{
	char	*error;

	error = NULL;
	if (access(full_path, F_OK))
		error = ft_strjoin(full_path, ": no such file or directory.\n");
	else if (access(full_path, X_OK))
		error = ft_strjoin(full_path, ": Permission denied.\n");
	else if (is_directory(full_path))
		error = ft_strjoin(cmd->token, ": Is a Directory.\n");
	return (error);
}

char	*getpath(char *cmd, char **path)
{
	char	*full_path;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	else
	{
		while (*path)
		{
			full_path = ft_strjoin_pre(*path, "/", cmd);
			if (!access(full_path, F_OK))
				return (full_path);
			free(full_path);
			path++;
		}
	}
	return (NULL);
}

void	exec_cmd(t_token *token, char **path, t_list **env,
		int std[2])
{
	char	*full_path;
	char	*error;
	t_token	*cmd;

	error = NULL;
	if ((cmd = get_cmd_token(token)) == NULL)
		return ;
	if ((full_path = getpath(cmd->token, path)))
	{
		if (!(error = ft_handle_errors(cmd, full_path)))
		{
			forkit(full_path, env, token, std);
			return (free_exec_cmd(error, full_path, path));
		}
		free(full_path);
	}
	error = (error) ? error : ft_strjoin(cmd->token, ": Command not found\n");
	run_redirection_with_errors(error, token, std);
	ft_free_strtab(path);
}

void	ft_exec(t_list *blt, t_list **env, t_token *node, int std[2])
{
	t_list			*bltin;
	t_token			*cmd;

	cmd = get_cmd_token(node);
	if (cmd == NULL)
	{
		run_redirection_with_errors(NULL, node, std);
		return ;
	}
	if (ft_exit(cmd))
		ft_putendl("42sh: you have suspended jobs.");
	else if ((bltin = ft_lstsearch(blt, cmd->token, &check_builtin)) != NULL)
		run_builtin(env, bltin, node, std);
	else
		exec_cmd(node, get_path(*env), env, std);
}
