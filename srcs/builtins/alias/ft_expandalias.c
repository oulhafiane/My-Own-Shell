/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expandalias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:48:22 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/18 23:47:13 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_replace(t_token_list *tokens, t_map *alias, int index)
{
	char			*val;
	t_token_list	*lst;

	val = alias->value;
	if ((lst = handle_quote(&val, 0)))
		ft_insert_at(tokens, lst->head, index);
}

char	ft_in_cycle(char *key)
{
	t_list	*lst;
	char	*k;

	lst = ft_getset(0)->last_aliases;
	while (lst)
	{
		k = lst->content;
		if (ft_strequ(k, key))
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	ft_addalias(t_map *alias, t_token_list *tokens, int i)
{
	t_list	*node;

	node = ft_lstnew(alias->key, ft_strlen(alias->key));
	ft_lstadd(&ft_getset(0)->last_aliases, node);
	ft_replace(tokens, alias, i);
}

void	ft_handle_alias(t_token_list *tokens)
{
	t_map		*alias;
	t_token		*token;
	int			i;

	i = 0;
	token = tokens->head;
	while (token)
	{
		if (i == 0 || ft_isjobseperator(token->tok_type))
		{
			if (i != 0)
			{
				i++;
				token = token->next;
			}
			if (token &&
				(alias = ft_getbykey(token->token, ALIAS)))
				if (!ft_in_cycle(alias->key))
					ft_addalias(alias, tokens, i);
		}
		i++;
		token = token ? token->next : NULL;
	}
}
