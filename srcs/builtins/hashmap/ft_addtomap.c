/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addtomap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:52:00 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 18:55:27 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_map		*ft_addtohashmap(char *key, char *value, char type)
{
	t_list	**l;
	t_map	*map;
	int		index;

	if ((map = ft_getbykey(key, type)))
	{
		if (type == INTERN && map->exported)
			ft_addexported(&ft_getset(0)->env, key, value);
		free(map->value);
	}
	else
	{
		l = ft_getset(0)->hashmap;
		map = malloc(sizeof(t_map));
		map->key = ft_strdup(key);
		map->hits = 0;
		map->type = type;
		index = ft_hash_calc(key);
		ft_lstadd(&l[index], ft_lstnew(map, 0));
	}
	map->value = ft_strdup(value);
	return (map);
}
