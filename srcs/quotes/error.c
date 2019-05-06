/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:23:52 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/05 19:15:18 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote.h"

int	*err_number(void)
{
	static int	err;

	return (&err);
}

/*
** Here we check if our line command end in proper way or not
*/

int	check_error(t_token_list *tokens)
{
	if (tokens->tail == NULL)
		return (0);
	if (tokens->tail->tok_type & SH_PIPE
			|| tokens->tail->tok_type & SH_DPIPE)
		return (1);
	return (0);
}
