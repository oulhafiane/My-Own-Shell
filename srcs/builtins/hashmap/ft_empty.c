/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:49:19 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/04 23:56:34 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_empty(char freeall)
{
	int		i;
	t_list	**l;
	t_map	*map;
	t_list	*list;
	t_list	*tmp;

	i = -1;
	l = ft_getset(0)->hashmap;
	while (++i < COUNT)
	{
		list = l[i];
		while (freeall && list)
		{
			map = list->content;
			tmp = list->next;
			if (freeall == ANYHASH || map->type == freeall)
			{
				free(map->key);
				free(map->value);
				free(list);
			}
			list = tmp;
		}
		l[i] = NULL;
	}
}
