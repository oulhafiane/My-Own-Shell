/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:23:34 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/06 18:01:17 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote.h"
#include "stdarg.h"

void	debug_msg(const char *fm, ...)
{
	va_list	ap;
	FILE	*file;

	va_start(ap, fm);
	file = fopen(DEBUG_TTY, "a+");
	vfprintf(file, fm, ap);
	va_end(ap);
	fclose(file);
}
