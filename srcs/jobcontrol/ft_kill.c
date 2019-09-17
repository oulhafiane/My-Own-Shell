/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:28:14 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/15 15:33:09 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void		ft_killjob(char **args)
{
	t_job	*job;

	if ((job = ft_getjob(args, "kill")))
		if (killpg(job->pgid, SIGTERM))
		{
			ft_printf("unable to kill job");
			ft_deljob(job, ft_getset(NULL));
		}
}

char		ft_jobid_expansion(t_token *token)
{
	t_token *prev;
	t_token	*head;

	head = token;
	if (token && ft_strequ(token->token, "kill") && (prev = token))
	{
		while ((token = token->next))
		{
			if (*token->token == '%')
			{
				ft_killjob(&token->token);
				prev->next = token->next;
				free(token->token);
				free(token);
				token = prev;
				continue ;
			}
			prev = token;
		}
		return (head->next ? 1 : 0);
	}
	return (1);
}
