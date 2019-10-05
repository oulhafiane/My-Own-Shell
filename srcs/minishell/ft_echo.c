/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 11:48:01 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/09/30 19:38:04 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	a builtin command, that print the arguments passed as parameter **args.
**	Note: The variable flag is used to indecated whether
**        we should print the new line or not
*/

void		ft_echo(char **args)
{
	int flag;

	flag = 0;
	if (*args && (*args)[0] == '-' && (*args)[1] == 'n')
	{
		flag = 1;
		args++;
	}
	while (*args)
	{
		ft_printf("%s", *args);
		if (*(args + 1))
			ft_putchar(' ');
		args++;
	}
	if (!flag)
		ft_printf("\n");
}
