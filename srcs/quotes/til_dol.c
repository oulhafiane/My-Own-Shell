/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   til_dol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:42:14 by amoutik           #+#    #+#             */
/*   Updated: 2019/09/27 15:15:27 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		handle_dollar(char **ptr, t_string *str)
{
	char	*head;
	char	*tmp;
	char	*env;
	t_list	*env_list;

	head = *ptr;
	env_list = get_t_line()->env;
	if (!ft_isalnum(*(head + 1)))
		return (0);
	else
		head++;
	while (*head && ft_isalnum(*head))
		head++;
	tmp = ft_strndup(*ptr, head - *ptr);
	if ((env = get_env_value((tmp + 1), env_list)) == NULL)
		env = "";
	free(tmp);
	while (*env)
		push(str, *env++);
	*ptr = head;
	return (1);
}

int		handle_tilda(char **ptr, t_string *str)
{
	char	*head;
	char	*home;
	int		j;
	t_list	*env_list;

	j = 0;
	head = *ptr;
	env_list = get_t_line()->env;
	if (*(head + 1) && (!ft_isspace(*(head + 1)) && (*(head + 1) != '/')))
		return (0);
	if ((home = get_env_value("HOME", env_list)) == NULL)
		home = "";
	while (home[j])
		push(str, home[j++]);
	*ptr = head + 1;
	return (1);
}
