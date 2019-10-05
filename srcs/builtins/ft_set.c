/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 01:46:32 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 01:48:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_set(void)
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
			if (map->type == INTERN)
				ft_printf_fd(1, "%s='%s'\n", map->key, map->value);
			l = l->next;
		}
		i++;
	}
}
