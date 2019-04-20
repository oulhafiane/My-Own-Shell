/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:52:28 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/19 23:08:25 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	a builtin command, that print the current location of the shell,
**	there two options to get that value (current location),
**	first it checks the environment variables if there is a $PWD variable,
**	if it exists, it will print it's value and the function will be stopped,
**	otherwise, it will search on $PATH if there is a path that contains
**	a program called pwd, and executes it.
**	NOTE : this second options it's working but I don't think this concept
**	is consistent with the subject, we have an autorised function getcwd
**	we can use it, so the next project of shell (21sh) i will use it.
*/

void	ft_pwd(char **args, t_list **lst)
{
	t_list		*cpy;
	t_env		*env;
	char		*pwd;

	(void)args;
	cpy = *lst;
	while (cpy)
	{
		env = (t_env*)cpy->content;
		if (ft_strcmp(env->name, "PWD") == 0)
		{
			ft_printf("%s\n", env->value);
			return ;
		}
		cpy = cpy->next;
	}
	ft_printf("%s\n", (pwd = getcwd(NULL, 0)));
	free(pwd);
}
