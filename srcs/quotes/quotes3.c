/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:50:02 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/21 16:13:51 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		is_special(char c)
{
	if (!ft_isalnum(c))
		return (1);
	return (0);
}

int				handle_dollar(char **line, char **new_line,
				t_list *env_list, t_spliter *spl)
{
	char	*head;
	char	*env;
	char	*tmp;
	int		len;

	if (spl->i == 1 && (*new_line)[0] == ' ')
		spl->i = 0;
	if (is_special(*((*line) + 1)))
		return (0);
	head = ++(*line);
	while (*head && !is_special(*head))
		head++;
	tmp = ft_strndup(*line, head - *line);
	if ((env = get_env_value(tmp, env_list)) == NULL)
		env = "";
	free(tmp);
	if ((len = ft_strlen(env)) > 0)
	{
		spl->len += len;
		*new_line = ft_realloc(*new_line, spl->len, spl->i);
	}
	while (*env)
		(*new_line)[(spl->i)++] = *env++;
	*line = head;
	return (1);
}

int				handle_tilda(char **line, char **new_line, t_list *env,
		t_spliter *spl)
{
	char	*head;
	char	*home;
	int		j;
	int		len;

	j = 0;
	if (ft_isalpha(*(*line + 1)))
		return (0);
	head = ++(*line);
	if ((home = get_env_value("HOME", env)) == NULL)
		home = "";
	if ((len = ft_strlen(home)) > 0)
	{
		spl->len += len;
		*new_line = ft_realloc(*new_line, spl->len, spl->i);
	}
	while (home[j])
		(*new_line)[(spl->i)++] = home[j++];
	*line = head;
	return (1);
}

t_command_list	*init_quotes(t_line *line, t_command_list *commands)
{
	init_list(commands);
	handle_quote(line, commands, -1, line->env);
	return (commands);
}
