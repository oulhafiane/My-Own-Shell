/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 21:26:42 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/10/05 21:22:28 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	needed by many functions,
**	it get the variabled named with char *name given on parameter
**	from the list t_list that contains all t_env elements.
*/

char		*get_env_value(char *name, t_list *lst)
{
	t_env	*env;

	while (lst)
	{
		env = (t_env*)lst->content;
		if (ft_strcmp(env->name, name) == 0)
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}

/*
**	a builtin command, it add new environment variable
**	to the list t_list that contains t_env elements.
*/

void		ft_addexported(t_list **lst, char *key, char *val)
{
	t_env	*env;
	t_list	*cpy;

	cpy = *lst;
	while (cpy)
	{
		env = (t_env*)cpy->content;
		if (ft_strcmp(env->name, key) == 0)
		{
			free(env->value);
			env->value = val ? ft_strdup(val) : ft_strdup("");
			return ;
		}
		cpy = cpy->next;
	}
	add_env(lst, key, val, 1);
}

/*
**	a builtin command, it removes all variables stored in **args
**	from the list t_list that contains t_env elements.
*/

void		ft_unset(char **args)
{
	t_list	*cpy;
	t_list	*previous;
	int		i;

	i = -1;
	while (args[++i] != NULL)
	{
		cpy = ft_getset(0)->env;
		previous = NULL;
		while (cpy != NULL)
		{
			if (ft_strcmp(((t_env*)cpy->content)->name, args[i]) == 0)
			{
				if (previous == NULL)
					ft_getset(0)->env = cpy->next;
				else
					previous->next = cpy->next;
				free_elem_env(cpy);
				break ;
			}
			if (ft_getbykey(args[i], INTERN))
				ft_hashdelete_one(args[i], INTERN);
			previous = cpy;
			cpy = cpy->next;
		}
	}
}
