/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proccess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:02:45 by sid-bell          #+#    #+#             */
/*   Updated: 2019/08/15 08:28:41 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_addprocess(t_job **job, pid_t pid, char wait)
{
	t_proc *process;

	process = malloc(sizeof(t_proc));
	process->pid = pid;
	process->exited = 0;
	process->stoped = 0;
	process->wait = wait;
	process->waiting = 0;
	ft_lstadd(&(*job)->pids, ft_lstnew(process, 0));
}

t_proc	*ft_getproc_byjob(t_job *job, pid_t pid)
{
	t_list	*lst;
	t_proc	*proc;

	lst = job->pids;
	while (lst)
	{
		proc = lst->content;
		if (proc->pid == pid)
			return (proc);
		lst = lst->next;
	}
	return (NULL);
}

t_proc	*ft_findjob(int pid)
{
	t_list		*lst;
	t_proc		*proc;

	lst = ft_getset(NULL)->list;
	while (lst)
	{
		if ((proc = ft_getproc_byjob(lst->content, pid)))
			return (proc);
		lst = lst->next;
	}
	return (NULL);
}
