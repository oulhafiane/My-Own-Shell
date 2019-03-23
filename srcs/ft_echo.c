/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 11:48:01 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/22 15:17:30 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	a builtin command, that print the arguments passed as parameter **args.
*/

void		ft_echo(char **args, t_list **env)
{
	(void)env;
	while (*args)
	{
		ft_printf("%s", *args);
		if (*(args + 1))
			ft_putchar(' ');
		args++;
	}
	ft_printf("\n");
}
