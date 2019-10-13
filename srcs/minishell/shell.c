/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 01:27:30 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/10/05 14:53:58 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	shell(t_list *blt, t_list **env, t_token_list *tokens)
{
	t_params	params;
	char		forgrounded;

	(void)blt;
	if (!tokens->head)
		return ;
	ft_getset(0)->env = *env;
	params.commands = NULL;
	signal(SIGCHLD, SIG_DFL);
	ft_expand_last_status(tokens->head);
	params.tokens = tokens;
	params.forkforbuiltin = 0;
	params.tmpenv = NULL;
	params.fd = dup(1);
	params.argv_index = 0;
	forgrounded = 1;
	ft_convert(tokens->head, &params);
	ft_exec_mode(tokens->head, &forgrounded);
	if ((params.commands && params.commands->next) || !forgrounded)
		params.forkforbuiltin = 1;
	ft_exec_job(&params, params.commands);
	ft_init_wait();
	ft_free_cmds(params.commands);
	close(params.fd);
	signal(SIGCHLD, ft_sigchld);
}
