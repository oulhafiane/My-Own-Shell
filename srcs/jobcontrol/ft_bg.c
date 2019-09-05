/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <idbellasaid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:01:46 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/04 17:38:13 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_bg(char **arg)
{
	t_job	*job;

	if (!(job = ft_getjob(arg, "bg")))
		return ;
	job->suspended = 0;
	job->foreground = 0;
	ft_resetstatus(job);
	if (!killpg(job->pgid, SIGCONT))
		ft_printf("[%d]\t+\t continued %s\n", job->id, job->cmd);
	else
	{
		ft_printf("unable to continue job %s\n", job->cmd);
		ft_deljob(job, ft_getset(NULL));
	}
}
