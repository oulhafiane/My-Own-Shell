/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:50:02 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/20 11:04:33 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		is_special(char c)
{
	const char	*escapchar = " !@#$%^&*()-_+=,;.\"\n\t\v\f\r\\";

	if (ft_strchr(escapchar, c))
		return (1);
	return (0);
}

int				handle_dollar(char **line, char **new_line,
				int *i, t_list *env_list)
{
	char *head;
	char *env;
	char *tmp;

	if (*i == 1 && (*new_line)[0] == ' ')
		*i = 0;
	if (is_special(*((*line) + 1)))
		return (0);
	head = ++(*line);
	while (*head && !is_special(*head))
		head++;
	tmp = ft_strndup(*line, head - *line);
	if ((env = get_env_value(tmp, env_list)) == NULL)
		env = "";
	free(tmp);
	while (*env)
		(*new_line)[(*i)++] = *env++;
	*line = head;
	return (1);
}

int				handle_tilda(char **line, char **new_line, int *i, t_list *env)
{
	char	*head;
	char	*home;
	int		j;

	j = 0;
	if (ft_isalpha(*((*line) + 1)))
		return (0);
	head = ++(*line);
	if ((home = get_env_value("HOME", env)) == NULL)
		home = "";
	while (home[j])
		(*new_line)[(*i)++] = home[j++];
	*line = head;
	return (1);
}

t_command_list	*init_quotes(t_line *line, t_command_list *commands)
{
	init_list(commands);
	handle_quote(line, commands, -1, line->env);
	return (commands);
}
