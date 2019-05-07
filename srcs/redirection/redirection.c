/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 23:21:38 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/07 00:25:37 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	handle_redirection(t_token *token)
{
	char	status;

	if ((status = handle_left_redirect(token)) != 0)
		return (status);
	if ((status = handle_right_redirect(token)) != 0)
		return (status);
	return (0);
}
