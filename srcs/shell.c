/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 01:27:30 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/17 22:14:36 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	The Fork Function
**	it creates a copy (child process) of the current process (parent process)
**	man fork -> for more info.
**	after that there will be two processes one is parent and the other is child
**	the child executes the cmds with the environment given on the parameters
**	the parent waits the child to finish
*/

static void	forkit(char *full_path, t_list **env, t_command_list *command)
{
	int			status;
	pid_t		father;
	char		**env_tab;
	t_duped		*current;
	t_redirect	*redirect;

	//Removed cmds
	//
	env_tab = env_to_tab(*env);
	signal(SIGINT, child_handler);
	redirect = handle_redirect(command);
	current = redirect->dup_head;
	father = fork();
	if (father > 0)
	{
		wait(&status);
		ft_free_strtab(env_tab);
		free_duped(redirect);
		signals();
	}
	else if (father == 0)
	{
		loop_dup(current);
		execve(full_path, redirect->command, env_tab);
		// Free t_redirect && t_duped
	}
}

/*
**	the command given need to be executed without searching in $PATH
**	because it's have with it the path like : /bin/ls
**	the function check if it's exist and it's permission to execute is OK
**	then sends it to forkit function 
**	otherwise, it prints an error msg.
*/

static void	exec_local(char **cmds, t_list **env, t_command_list *command)
{
	if (access(*cmds, F_OK) == 0)
	{
		if (access(*cmds, X_OK) == 0)
			forkit(*cmds, env, command);
		else
			ft_printf_fd(2, "%s: Permission denied.\n", *cmds);
	}
	else
		ft_printf_fd(2, "%s: Command not found.\n", *cmds);
}

/*
**	the command given to be search in all paths stored in environment variable $PATH
**	then if it's exist it checks it's permission to execute
**	then sends it to forkit function
**	otherwise, it prints an error msg.
*/

void		exec_cmd(t_command_list *command, char **path, t_list **env)
{
	char	*full_path;
	char	*error;
	char	**head_path;
	char	*binary_file;

	error = NULL;
	head_path = path;
//	if((cmds = list_to_chars(command)) == NULL)
//		return ;
	binary_file = command->head->argv;
	if (binary_file != NULL)
	{
		while (*path)
		{
			full_path = ft_strjoin_pre(*path, "/", binary_file);
			if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			{
				forkit(full_path, env, command);
				free_exec_cmd(error, full_path, head_path);
				return ;
			}
			else if (error != NULL && access(full_path, F_OK) == 0)
				error = ft_strjoin(full_path, ": Permission denied.\n");
			path++;
			free(full_path);
		}
		print_error(error, binary_file);
	}
	ft_free_strtab(head_path);
}

static void	shell(t_list *blt, t_list **env, t_command_list *command)
{
	char			**cmds;
	t_list			*bltin;

	if (command->head != NULL)
	{
		if(is_piped(command))
		{
			//removed count
			handle_piping(command, env, blt);
			return ;
		}
		if((cmds = list_to_chars(command)) == NULL)
			return ;
		if (ft_strcmp(*cmds, "exit") == 0)
		{
			ft_free_strtab(cmds);
			exit(-1);
		}
		else if ((bltin = ft_lstsearch(blt, *cmds, &check_builtin)) != NULL)
			run_builtin(env, cmds, bltin);
		else if (ft_strchr(*cmds, '/') != NULL)
			exec_local(cmds, env, command);
		else
			exec_cmd(command, get_path(*env), env);
		ft_free_strtab(cmds);
	}
}

/*
**	The loop function of minishell
**	it prints the minishell msg : My_Minishell $>
**	and reads from the input standard the command
**	and check it which type is it : exit, builtins, Cmd with path, Cmd Without Path
**	and sends the list of agruments to appropriate function.
**	
**	Notes : (libft functions)
**	get_next_line  : reads a line from the standard input.
**	ft_strsplit_ws : splits a line to a multiple words by whitespace delimiters
**			 returns a char** and last pointer is NULL.
**	free_strtab    : frees all strings (char**) returned by ft_strsplit_ws. 
*/

static void	run_shell(t_list *blt, t_list **env, t_list **history)
{
	t_line			*new_line;
	t_command_list	commands;
	t_command_list	*cmds;
	t_command_list	*cmd;

	new_line = init_line();
	new_line->tail_history = history;
	new_line->old_command = NULL;
	while(read_line(new_line) == 0)
	{
		add_history(new_line);
		cmds = init_quotes(get_t_line(), &commands);
		while (cmds->index)
		{
			cmd = separated_by_del(cmds, ';');
			shell(blt, env, cmd);
			//Added
			free_list(cmd, 1);
			//
		}
		//Added
		free_list(&commands, 0);
		//
		free_line();
		new_line = init_line();
		free(new_line->old_command);
		new_line->old_command = NULL;
	}
	free_line();
}

/*
**	The Main Function of Minishell
**	it initiates the builtins and environment lists,
**	after calls the loop function of minishell,
**	after frees all memory allocated on the heap
*/

int		main(int ac, char **av, char **ev)
{
	t_list		*env;
	t_list		*blt;
	t_list		*history;

	(void)ac;
	(void)av;
	blt = NULL;
	env = NULL;
	history = NULL;
	init_env(&env, ev);
	init_builtin(&blt);
	signals();
	run_shell(blt, &env, &history);
	free_gnl(0);
	free_env(env);
	free_builtin(blt);
	return (0);
}
