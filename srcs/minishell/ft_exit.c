/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:28:12 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 14:53:25 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	ft_status(t_list *lst)
{
	t_job *job;

	while (lst)
	{
		job = lst->content;
		if (job->suspended)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void		ft_exit(char **argv, t_params *params)
{
	t_container		*container;
	unsigned char	r;

	if (ft_getset(0)->interractive)
		ft_printf("exit\n");
	container = ft_getset(NULL);
	if (!ft_status(container->list) && container->time_to_exit)
	{
		ft_printf("There are stopped jobs\n");
		container->time_to_exit = 0;
	}
	else
	{
		r = 0;
		free_line();
		ft_free_aliases();
		free(ft_getset(NULL));
		if (argv[0] && !ft_isnumber(argv[0]) && (r = 255))
			ft_printf_fd(2, "42sh: exit: numeric argument required\n");
		else if (argv[0])
			r = ft_atoi(argv[0]);
		ft_free_cmds(params->commands);
		exit(r);
	}
}
