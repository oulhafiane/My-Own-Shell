/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 00:58:20 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 01:32:54 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list	*ft_cpyenv(void)
{
	t_list	*new;
	t_list	*env;
	t_env	*envnode;
	t_env	*newnode;
	t_list	*node;

	env = ft_getset(0)->env;
	new = NULL;
	while (env)
	{
		envnode = env->content;
		newnode = malloc(sizeof(t_env));
		newnode->name = ft_strdup(envnode->name);
		newnode->value = ft_strdup(envnode->value);
		node = ft_lstnew(newnode, 0);
		ft_lstadd(&new, node);
		env = env->next;
	}
	return (new);
}
