/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:42:11 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/04 17:43:57 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_number(char *str)
{
	while (*str && !ft_isspace(*str))
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
