/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rvalue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:03:21 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/20 00:51:09 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_set_last_rvalue(int rvalue)
{
	t_container *container;

	container = ft_getset(NULL);
	container->last_status = rvalue;
}

int		ft_get_last_rvalue(void)
{
	t_container *container;

	container = ft_getset(NULL);
	return (container->last_status);
}

void	ft_expand_last_status(t_token *token)
{
	int			last;
	char		*ptr;

	while (token)
	{
		if (token->tok_type & SH_SEMI
			|| token->tok_type & SH_DPIPE
			|| token->tok_type & SH_LOGAND)
			return ;
		if (token->tok_type & SH_WORD)
		{
			last = ft_getset(NULL)->last_status;
			if ((ptr = ft_strstr(token->token, "$?")))
				ft_str_replace(&token->token, "$?", ft_itoa(last));
		}
		token = token->next;
	}
}
