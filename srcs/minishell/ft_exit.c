/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:28:12 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/18 15:28:19 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		ft_exit(t_token *cmd)
{
	t_container *container;

	container = ft_getset(NULL);
	if (ft_strcmp(cmd->token, "exit") == 0)
	{
		if (container->list && container->time_to_exit)
			container->time_to_exit = 0;
		else
		{
			free(ft_getset(NULL));
			free_line();
			exit(ft_atoi(cmd->next ? cmd->next->token : "0"));
		}
		return (1);
	}
	else
		container->time_to_exit = 1;
	return (0);
}
