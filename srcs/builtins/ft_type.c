/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 21:15:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/04 16:17:18 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_type(char **args)
{
	int		i;
	t_list	*l;
	char	*file;

	i = 0;
	l = ft_getset(0)->builtins;
	while (args[i])
	{
		if (ft_is_builtin(args[i], l))
			ft_printf("%s is a shell builtin\n", args[i]);
		else if ((file = ft_getvlaue_bykey(args[i], ALIAS)))
			ft_printf("%s is alias for %s\n", args[i], file);
		else if ((file = ft_getvlaue_bykey(args[i], COMMANDS)))
			ft_printf("%s is hashed (%s)\n", args[i], file);
		else if ((file = getpath(args[i], get_path(ft_getset(0)->env))))
			ft_printf("%s is %s\n", args[i], file);
		else
			ft_printf("42sh: type %s: not found\n", args[i]);
		i++;
	}
}
