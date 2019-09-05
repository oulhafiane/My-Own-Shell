/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:06:16 by sid-bell          #+#    #+#             */
/*   Updated: 2019/08/15 08:27:25 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_free_job(t_job *job)
{
	t_list		*pids;
	t_list		*tmp;
	t_proc		*proc;

	pids = job->pids;
	while (pids)
	{
		proc = pids->content;
		kill(proc->pid, SIGKILL);
		tmp = pids->next;
		free(pids->content);
		free(pids);
		pids = tmp;
	}
	free(job->cmd);
	free(job);
}
