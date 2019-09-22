/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 03:10:48 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/09/22 05:19:14 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_interns(t_token_list *tokens, t_token **token, t_line *line)
{
	int		i;

	while (*token != NULL)
	{
		if ((i = ft_strchri((*token)->token, '=')) != 0)
		{
			(*token)->token[i] = '\0';
			add_env(&(line->intern), (*token)->token,
					(*token)->token + i + 1, 1); 
			(*token)->token[i] = '=';
			tokens->head = (*token)->next;
		}
		else
			return ;
		*token = (*token)->next;
	}
}
