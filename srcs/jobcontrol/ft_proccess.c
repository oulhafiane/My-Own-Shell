/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proccess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:02:45 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/03 13:52:00 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

t_job	*ft_pid_lookup(pid_t pid, t_proc **procc)
{
	t_list	*list;
	t_proc	*proc;
	t_list	*pids;

	list = ft_getset(NULL)->list;
	while (list)
	{
		pids = ((t_job *)list->content)->pids;
		while (pids)
		{
			proc = pids->content;
			if (proc->pid == pid)
			{
				*procc = proc;
				return (list->content);
			}
			pids = pids->next;
		}
		list = list->next;
	}
	return (NULL);
}

void	ft_addprocess(t_job **job, pid_t pid)
{
	t_proc *process;

	process = malloc(sizeof(t_proc));
	process->pid = pid;
	process->exited = 0;
	process->stoped = 0;
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
