/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:57:10 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/06 20:28:29 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int search_semi(t_list *blt, t_list **env, t_token_list *tokens)
{
	t_token     *ptr;

	ptr = tokens->head;
	while (ptr)
	{
		if ((ptr->tok_type & SH_SEMI) != 0)
		{
			tokens->head = ptr->next;
			shell(blt, env, tokens);
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

static void		run_shell(t_list *blt, t_line *line)
{
	t_token_list	*tokens;
	t_token			*head;

	line->std[0] = dup(0);
	line->std[1] = dup(1);
	line->std[2] = dup(2);
	while (read_line(line) == 0)
	{
		if (!ft_str_isnull(line->command))
		{
			if ((tokens = handle_quote(&line->command)) != NULL)
			{
				head = tokens->head;
				add_history(line);
				shell(blt, &(line->env), tokens);
				print_tokens(tokens);
				search_semi(blt, &(line->env), tokens);
				tokens->head = head;
				free_token_list(tokens);
			}
		}
		free_line();
		line = init_line();
	}
	free_line();
}

/*
 **	The Main Function of Minishell
 **	it initiates the builtins and environment lists,
 **	after calls the loop function of minishell,
 **	after frees all memory allocated on the heap
 */

int			main(int ac, char **av, char **ev)
{
	t_list		*env;
	t_list		*blt;
	t_list		*history;
	t_line		*new_line;

	(void)ac;
	(void)av;
	blt = NULL;
	env = NULL;
	history = NULL;
	init_env(&env, ev);
	init_builtin(&blt);
	signals();
	new_line = init_line();
	new_line->tail_history = &history;
	new_line->env = env;
	new_line->copy = NULL;
	run_shell(blt, new_line);
	free(new_line->copy);
	free_gnl(0);
	free_env(env);
	free_builtin(blt);
	return (0);
}
