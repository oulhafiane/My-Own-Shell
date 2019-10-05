/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:38:24 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 18:50:34 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_get_kv(char *str, char **key, char **val)
{
	int		len;
	int		i;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			*key = ft_strsub(str, 0, i);
			*val = ft_strsub(str, i + 1, len);
			return ;
		}
		i++;
	}
	*key = str;
	*val = NULL;
	return ;
}

int		ft_charpos(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_alias(char **args)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_charpos(args[i], '=') > 0)
		{
			ft_get_kv(args[i], &key, &value);
			ft_addtohashmap(key, value, ALIAS);
			free(key);
			free(value);
		}
		else
			ft_show_aliases(args[i]);
		i++;
	}
	if (i == 0)
		ft_show_aliases(NULL);
}
