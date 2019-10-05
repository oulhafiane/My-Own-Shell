/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hashmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:53:01 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/04 23:53:09 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_print_hash_list(void)
{
	int		i;
	t_list	*l;
	t_list	**lst;
	t_map	*map;

	i = 0;
	lst = ft_getset(0)->hashmap;
	ft_printf("hits\t command\n");
	while (i < COUNT)
	{
		l = lst[i];
		while (l)
		{
			map = l->content;
			if (map->type == COMMANDS)
				ft_printf("%3d\t %s\n", map->hits, map->value);
			l = l->next;
		}
		i++;
	}
}
