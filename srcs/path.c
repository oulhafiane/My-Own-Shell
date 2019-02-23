/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:11:37 by amoutik           #+#    #+#             */
/*   Updated: 2019/02/23 10:54:31 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			is_accessible(char *full_path)
{
	if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		return (1);
	return (0);
}

int			full_path(char **cmd, char **path_env)
{
	char	*full_path;

	if (*cmd == NULL)
		return (ECMD);
	while (*path_env)
	{
		full_path = ft_strjoin_pre(*path_env, "/", *cmd);
		if (is_accessible(full_path))
		{
			free(*cmd);
			*cmd = full_path;
			return (SUCCESS);
		}
		else if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == -1)
			return (EACCESS);
		path_env++;
		free(full_path);
	}
	if (is_accessible(*cmd))
		return (SUCCESS);
	else if (access(*cmd, F_OK) == 0 && access(*cmd, X_OK) == -1)
		return (EACCESS);
	return (EFILE);
}
