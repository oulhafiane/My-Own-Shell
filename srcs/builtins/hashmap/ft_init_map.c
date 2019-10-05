/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:47:46 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/04 23:48:07 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_init_hash(t_list *env)
{
	t_list	**l;

	ft_getset(0)->env = env;
	l = malloc(sizeof(t_list *) * COUNT);
	ft_getset(0)->hashmap = l;
	ft_empty(0);
}
