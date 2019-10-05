/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapdelete_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:50:06 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/04 23:56:46 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_free(t_map *alias, t_list **next, t_list *lst)
{
	free(alias->key);
	free(alias->value);
	*next = lst->next;
	free(lst);
}

void		ft_hashdelete_one(char *key, char type)
{
	t_list	*lst;
	t_list	*prev;
	t_map	*map;
	t_list	*next;
	int		index;

	index = ft_hash_calc(key);
	lst = ft_getset(0)->hashmap[index];
	prev = NULL;
	while (lst)
	{
		map = lst->content;
		if (map->type == type && ft_strequ(key, map->key))
		{
			ft_free(map, &next, lst);
			if (prev)
				prev->next = next;
			else
				ft_getset(0)->hashmap[index] = next;
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
}
