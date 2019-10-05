/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 01:04:33 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 18:40:22 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#define ENV_ENTRY 1
#define INTEREN_ENTRY 2

char	ft_kv_type(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (!ft_isintern(argv[i]))
			return (ENV_ENTRY);
		i++;
	}
	return (INTEREN_ENTRY);
}

int		ft_rrun(t_params *params, t_command *cmd)
{
	t_builtin	*blt;
	int			index;

	index = params->argv_index;
	if ((blt = ft_is_builtin(cmd->argv[index],
			ft_getset(0)->builtins)))
	{
		if (params->forkforbuiltin)
			ft_fork(params, NULL, cmd, blt);
		else
			run_builtin(params, blt->f, cmd->argv + index, params->tokens);
	}
	else
		return (ft_run(params, cmd));
	return (0);
}

void	ft_addintern(t_params *params, char *str, int type)
{
	char	*key;
	char	*value;

	ft_get_kv(str, &key, &value);
	if (type == ENV_ENTRY)
		ft_addexported(&params->tmpenv, key, value);
	else
		ft_addtohashmap(key, value, INTERN);
}

int		ft_getinterns(t_params *params, t_command *cmd)
{
	char	**argv;
	int		i;
	char	type;

	type = ft_kv_type(cmd->argv);
	params->tmpenv = ft_cpyenv();
	argv = cmd->argv;
	i = 0;
	while (argv[i])
	{
		if (ft_isintern(argv[i]))
		{
			ft_addintern(params, argv[i], type);
		}
		else
		{
			params->argv_index = i;
			return (ft_rrun(params, cmd));
		}
		i++;
	}
	return (1);
}
