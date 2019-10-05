/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 02:58:39 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/03 13:51:32 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_sort(t_list *list)
{
	t_list	*head;
	t_job	*job;
	char	c;

	c = 1;
	head = list;
	while (c)
	{
		c = 0;
		while (list)
		{
			if (list->next)
			{
				job = list->next->content;
				if (((t_job *)list->content)->id < job->id && (c = 1))
				{
					list->next->content = list->content;
					list->content = job;
				}
			}
			list = list->next;
		}
		list = head;
	}
}

t_job	*ft_getbypgid(t_list *list, pid_t pgid)
{
	t_job	*job;

	while (list)
	{
		job = list->content;
		if (job->pgid == pgid)
			return (list->content);
		list = list->next;
	}
	return (NULL);
}

t_job	*ft_getjob_byindex(int index)
{
	t_list		*list;
	t_job		*job;
	t_container	*container;

	container = ft_getset(NULL);
	list = container->list;
	while (list)
	{
		job = list->content;
		if (job->id == index)
			return (list->content);
		list = list->next;
	}
	return (NULL);
}

int		ft_lstcount(t_list *list)
{
	int count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

char	ft_isjobseperator(enum e_token_type type)
{
	return (type & SH_DPIPE
			|| type & SH_LOGAND
			|| type & SH_SEMI
			|| type & SH_IMPER);
}
