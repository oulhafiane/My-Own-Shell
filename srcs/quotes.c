/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:58:15 by amoutik           #+#    #+#             */
/*   Updated: 2019/02/20 10:38:19 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		push_stack(char *flag_quote, char buf)
{
	if (*flag_quote == NOTHING)
		*flag_quote = buf;
	else if (*flag_quote == buf)
		*flag_quote = NOTHING;
}

int		check_stack(char flag_quote)
{
	if (flag_quote == NOTHING)
		return (0);
	if (flag_quote == SINGLE_QUOTE)
		ft_printf("\nquotes> ");
	else if (flag_quote == DOUBLE_QUOTE)
		ft_printf("\ndouble quotes> ");
	return (-1);
}
