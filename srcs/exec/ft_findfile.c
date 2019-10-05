/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 14:51:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 14:51:21 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_findfile(char *name, char **error)
{
	char	*file;
	t_stat	state;

	if ((file = ft_getvlaue_bykey(name, COMMANDS)))
	{
		if (access(file, F_OK))
			file = NULL;
		else
			file = ft_strdup(file);
	}
	if (!file && ((file = getpath(name, get_path(ft_getset(0)->env)))))
	{
		ft_addtohashmap(name, file, COMMANDS);
		ft_getvlaue_bykey(name, COMMANDS);
	}
	if (file && !stat(file, &state))
	{
		if (S_ISREG(state.st_mode))
			return (file);
		else if (S_ISDIR(state.st_mode))
			*error = "42sh: %s: is a directory\n";
		else
			*error = "42sh: %s: permission denied\n";
	}
	return (NULL);
}
