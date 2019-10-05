/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 17:44:55 by sid-bell          #+#    #+#             */
/*   Updated: 2019/08/16 20:37:10 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

t_job	*ft_getjob(char **arg, char *caller)
{
	t_container *container;
	int			jobid;
	t_job		*job;

	jobid = -1;
	if (arg && *arg)
	{
		if (**arg != '%')
		{
			ft_printf_fd(2, "%s: job not found: %s\n", caller, *arg);
			return (NULL);
		}
		if (*(*arg + 1))
			jobid = ft_atoi(*arg + 1);
	}
	container = ft_getset(NULL);
	if (jobid == -1)
		return (container->current);
	if (!(job = ft_getjob_byindex(jobid)))
	{
		ft_printf_fd(2, "%s %d: no such job\n", caller, jobid);
		return (NULL);
	}
	return (job);
}

t_job	*ft_jobgetter(t_job *job, char reset)
{
	static t_job *j;

	if (job)
		j = job;
	if (reset)
		j = 0;
	return (j);
}
