/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:26:47 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/01 19:24:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*getpath(char *cmd, char **path)
{
	char	*full_path;
	int		i;

	full_path = NULL;
	if (ft_strchr(cmd, '/'))
		full_path = ft_strdup(cmd);
	else
	{
		i = 0;
		while (path[i])
		{
			full_path = ft_strjoin_pre(path[i], "/", cmd);
			if (!access(full_path, F_OK))
				break ;
			free(full_path);
			full_path = NULL;
			i++;
		}
	}
	ft_free_array(path);
	return (full_path);
}

t_builtin	*ft_is_builtin(char *cmd, t_list *blt)
{
	t_list *lst;

	if ((lst = ft_lstsearch(blt, cmd, &check_builtin)))
		return (lst->content);
	return (NULL);
}
