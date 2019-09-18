/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 01:27:30 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/09/18 16:05:44 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

int			check_and_or(t_token *token)
{
	while (token)
	{
		if (token->tok_type & SH_SEMI)
			return (0);
		if (token->tok_type == SH_DPIPE)
			return (SH_LOGOR);
		if (token->tok_type & SH_LOGAND)
			return (SH_LOGAND);
		token = token->next;
	}
	return (0);
}

void		next_and_or(t_token_list *tokens)
{
	t_token		*token;

	token = tokens->head;
	while (token)
	{
		if ((token->tok_type & SH_DPIPE) ||
			(token->tok_type & SH_SEMI) || token->tok_type & SH_LOGAND)
		{
			tokens->head = token->next;
			return ;
		}
		token = token->next;
	}
}

void		pre_run(t_list *blt, t_list **env, t_token_list *tokens)
{
	int		std[2];
	int		pp[2];
	char	piping;

	std[0] = 0;
	std[1] = 1;
	if ((piping = check_pipe(tokens->head)) && pipe(pp) != -1)
		std[1] = pp[1];
	ft_exec(blt, env, tokens->head, std);
	while (piping)
	{
		next_pipe(tokens);
		std[0] = pp[0];
		std[1] = 1;
		close(pp[1]);
		if ((piping = check_pipe(tokens->head)) && pipe(pp) != -1)
			std[1] = pp[1];
		if (tokens->head)
			ft_exec(blt, env, tokens->head, std);
		close(std[0]);
	}
	ft_init_wait();
}

void		shell(t_list *blt, t_list **env, t_token_list *tokens)
{
	int			and_or;
	int			status;

	ft_set_last_rvalue(127);
	pre_run(blt, env, tokens);
	while ((and_or = check_and_or(tokens->head)))
	{
		next_and_or(tokens);
		status = ft_get_last_rvalue();
		if (((and_or & SH_LOGOR) && status)
			|| ((and_or & SH_LOGAND) && !status))
		{
			ft_set_last_rvalue(127);
			pre_run(blt, env, tokens);
		}
	}
}
