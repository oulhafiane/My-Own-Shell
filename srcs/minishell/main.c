/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:57:10 by amoutik           #+#    #+#             */
/*   Updated: 2019/09/22 05:14:21 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		search_semi(t_list *blt, t_line *line, t_token_list *tokens)
{
	t_token		*ptr;

	ptr = tokens->head;
	while (ptr)
	{
		if ((ptr->tok_type & SH_SEMI) != 0)
		{
			tokens->head = ptr->next;
			shell(blt, line, tokens);
		}
		ptr = ptr->next;
	}
	return (0);
}

/*
**  The loop function of minishell
**  it prints the minishell msg : My_Minishell $>
**  and reads from the input standard the command
**  and check it which type is it : exit, builtins,
**                                  Cmd with path, Cmd Without Path
**  and sends the list of agruments to appropriate function.
**  Notes : (libft functions)
**  get_next_line  : reads a line from the standard input.
**  ft_strsplit_ws : splits a line to a multiple words by whitespace delimiters
**           returns a char** and last pointer is NULL.
**  free_strtab    : frees all strings (char**) returned by ft_strsplit_ws.
*/

void			print_tokens(t_token_list *tokens)
{
	t_token		*token;
	int			i;
	char		type[1000];

	token = tokens->head;
	ft_debug("==========\n");
	i = -1;
	while (++i < tokens->node_count)
	{
		ft_memset(type, 0, 1000);
		if ((token->tok_type & SH_WORD) != 0)
			ft_strcat(type, "| word ");
		if ((token->tok_type & SH_PIPE) != 0)
			ft_strcat(type, "| pipe ");
		if ((token->tok_type & SH_REDIRECTION) != 0)
			ft_strcat(type, "| redirection ");
		if ((token->tok_type & SH_SEMI) != 0)
			ft_strcat(type, "| semi ");
		if ((token->tok_type & SH_QUOTED) != 0)
			ft_strcat(type, "| quoted ");
		if ((token->tok_type & SH_DPIPE) != 0)
			ft_strcat(type, "| doublePipe ");
		if ((token->tok_type & SH_IMPER) != 0)
			ft_strcat(type, "| imper ");
		if ((token->tok_type & SH_LOGAND) != 0)
			ft_strcat(type, "| logand ");
		ft_debug("%s => %s\n", token->token, type);
		token = token->next;
	}
	ft_debug("==========\n");
}

static void		run_shell(t_list *blt, t_line *line)
{
	t_token_list	*tokens;
	t_token			*head;

	while (read_line(line) == 0)
	{
		while (1)
		{
			if (ft_str_isnull(line->command) ||
				(tokens = handle_quote(&line->command)) == NULL)
				break ;
			print_tokens(tokens);
			add_history(line);
			if (parse_heredoc(tokens) != 0 && free_token_list(tokens))
				continue ;
			head = tokens->head;
			shell(blt, line, tokens);
			search_semi(blt, line, tokens);
			tokens->head = head;
			free_token_list(tokens);
			break ;
		}
		free_line();
		(line = init_line()) ? ft_notify() : 0;
	}
	ft_printf(WRONG_READ);
	free_line();
}

void	free_all(t_line *new_line, t_list *env, t_list *blt, t_list *intern)
{
	free(new_line->copy);
	//free_gnl(0);
	free_env(env);
	free_env(intern);
	free_builtin(blt);
}

/*
**	The Main Function of Minishell
**	it initiates the builtins and environment lists,
**	after calls the loop function of minishell,
**	after frees all memory allocated on the heap
*/

int				main(int ac, char **av, char **ev)
{
	t_list		*intern;
	t_list		*env;
	t_list		*blt;
	t_list		*history;
	t_line		*new_line;

	(void)ac;
	(void)av;
	blt = NULL;
	env = NULL;
	history = NULL;
	ft_init_jobcontrol();
	init_env(&env, ev);
	init_env(&intern, ev);
	init_builtin(&blt);
	signals();
	new_line = init_line();
	new_line->tail_history = &history;
	new_line->env = env;
	new_line->intern = intern;
	new_line->copy = NULL;
	run_shell(blt, new_line);
	free_all(new_line, env, blt, intern);
	return (0);
}
