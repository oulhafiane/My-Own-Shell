/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 01:27:30 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/07 16:08:06 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		is_directory(const char *path)
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

static void	exec_local(t_token *token, t_list **env, int std[2])
{
	if (access(token->token, F_OK) == 0)
	{
		if (is_directory(token->token))
			ft_printf_fd(2, "%s: Is a Directory.\n", token->token);
		else if (access(token->token, X_OK) == 0)
			forkit(token->token, env, token, std);
		else
			ft_printf_fd(2, "%s: Permission denied.\n", token->token);
	}
	else
		ft_printf_fd(2, "%s: Command not found.\n", token->token);
}

/*
**	the command given to be search in all paths stored
**  in environment variable $PATH
**	then if it's exist it checks it's permission to execute
**	then sends it to forkit function
**	otherwise, it prints an error msg.
*/

static void	exec_cmd(t_token *token, char **path, t_list **env,
		int std[2])
{
	char	*full_path;
	char	*error;
	char	**head_path;

	error = NULL;
	head_path = path;
	while (*path)
	{
		full_path = ft_strjoin_pre(*path, "/", token->token);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			forkit(full_path, env, token, std);
			return (free_exec_cmd(error, full_path, head_path));
		}
		else if (error != NULL && access(full_path, F_OK) == 0)
			error = ft_strjoin(full_path, ": Permission denied.\n");
		path++;
		free(full_path);
	}
	print_error(error, token->token);
	ft_free_strtab(head_path);
}

static void	exec(t_list *blt, t_list **env, t_token *node, int std[2])
{
	t_list			*bltin;

	if (node == NULL)
		return ;
	if (ft_strcmp(node->token, "exit") == 0)
	{
		free_line();
		exit(-1);
	}
	else if ((bltin = ft_lstsearch(blt, node->token, &check_builtin)) != NULL)
		run_builtin(env, bltin, node, std);
	else if (ft_strchr(node->token, '/') != NULL)
		exec_local(node, env, std);
	else
		exec_cmd(node, get_path(*env), env, std);
}

void	shell(t_list *blt, t_list **env, t_token_list *tokens)
{
	int		std[2];
	int     pp[2];
	char    piping;

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
	close(pp[1]);
	close(pp[0]);
}
