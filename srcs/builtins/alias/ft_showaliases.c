/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_showaliases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:46:09 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/04 16:12:12 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_print_alias_list(void)
{
	int		i;
	t_list	*l;
	t_list	**lst;
	t_map	*map;

	i = 0;
	lst = ft_getset(0)->hashmap;
	while (i < COUNT)
	{
		l = lst[i];
		while (l)
		{
			map = l->content;
			if (map->type == ALIAS)
				ft_printf_fd(1, "alias %s='%s'\n", map->key, map->value);
			l = l->next;
		}
		i++;
	}
}

void	ft_show_aliases(char *key)
{
	char	*value;

	if (key)
	{
		if ((value = ft_getvlaue_bykey(key, ALIAS)))
			ft_printf_fd(1, "alias %s='%s'\n", key, value);
		else
			ft_printf_fd(2, "42sh: alias: %s: not found\n", key);
		return ;
	}
	ft_print_alias_list();
}
