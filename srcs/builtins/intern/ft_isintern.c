/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isintern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 00:33:51 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 14:09:00 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	ft_isintern(char *cmd)
{
	char	*key;
	char	*value;

	if (!ft_strchr(cmd, '='))
		return (0);
	if (ft_isdigit(cmd[0]))
		return (0);
	ft_get_kv(cmd, &key, &value);
	return (ft_str_isalnum(key));
}
