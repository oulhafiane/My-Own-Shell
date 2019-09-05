/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <idbellasaid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 01:27:30 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/09/01 22:17:06 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_directory(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (M_ISDIR(statbuf.st_mode));
}

/*
**	the command given need to be executed without searching in $PATH
**	because it's have with it the path like : /bin/ls
**	the function check if it's exist and it's permission to execute is OK
**	then sends it to forkit function
**	otherwise, it prints an error msg.
*/

/*
**	the command given to be search in all paths stored
**  in environment variable $PATH
**	then if it's exist it checks it's permission to execute
**	then sends it to forkit function
**	otherwise, it prints an error msg.
*/

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

static void	exec_cmd(t_token *token, char **path, t_list **env,
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

static void	exec(t_list *blt, t_list **env, t_token *node, int std[2])
{
	t_list			*bltin;
	t_token			*cmd;

	cmd = get_cmd_token(node);
	if (cmd == NULL)
	{
		run_redirection_with_errors(NULL, node, std);
		return ;
	}
	if (ft_strcmp(cmd->token, "exit") == 0)
	{
		if (ft_getset(NULL)->list)
			ft_putendl("42sh: you have suspended jobs.");
		else
		{
			free(ft_getset(NULL));
			free_line();
			exit(ft_atoi(cmd->next ? cmd->next->token : "0"));
		}
	}
	else if ((bltin = ft_lstsearch(blt, cmd->token, &check_builtin)) != NULL)
		run_builtin(env, bltin, node, std);
	else
		exec_cmd(node, get_path(*env), env, std);
}

void		shell(t_list *blt, t_list **env, t_token_list *tokens)
{
	int		std[2];
	int		pp[2];
	char	piping;

	std[0] = 0;
	std[1] = 1;
	if ((piping = check_pipe(tokens->head)) && pipe(pp) != -1)
		std[1] = pp[1];
	exec(blt, env, tokens->head, std);
	while (piping)
	{
		next_pipe(tokens);
		std[0] = pp[0];
		std[1] = 1;
		close(pp[1]);
		if ((piping = check_pipe(tokens->head)) && pipe(pp) != -1)
			std[1] = pp[1];
		if (tokens->head)
			exec(blt, env, tokens->head, std);
		close(std[0]);
	}
	ft_init_wait();
}
