/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 20:43:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 18:53:36 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_env(void)
{
	t_list	*lst;
	t_list	*cpy;
	t_env	*env;

	lst = ft_getset(0)->env;
	cpy = lst;
	while (cpy)
	{
		env = (t_env*)cpy->content;
		ft_printf("export %s=%s\n", env->name, env->value);
		cpy = cpy->next;
	}
}

static int	ft_getflags(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (*cmd[i] == '-')
		{
			if (ft_strequ(cmd[i] + 1, "p"))
			{
				ft_env();
				return (-2);
			}
			else
			{
				ft_printf_fd(2, "42sh: export: -%c: invalid option\n", cmd[i]);
				return (-1);
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

void		ft_export(char **args)
{
	int		i;
	char	*key;
	char	*value;
	char	export;
	t_map	*map;

	if (!args[0])
	{
		ft_env();
		return ;
	}
	if ((i = ft_getflags(args)) < 0)
	{
		if (i == -1)
			ft_printf_fd(2,
				"42sh: usage: export [-p] [name[=value] ...]\n");
		return ;
	}
	while (args[i])
	{
		export = ft_strchr(args[i], '=') ? 1 : 0;
		ft_get_kv(args[i], &key, &value);
		if (ft_isdigit(key[0]) || !ft_str_isalnum(key))
			ft_printf("42sh: export: `%s': not a valid identifier\n", key);
		else
		{
			if (!export)
			{
				if ((map = ft_getbykey(key, INTERN)))
				{
					map->exported = 1;
					value = map->value;
				}
				else
				{
					i++;
					continue ;
				}
			}
			ft_addtohashmap(key, value, INTERN);
			ft_addexported(&ft_getset(0)->env, key, value);
		}
		i++;
	}
}
