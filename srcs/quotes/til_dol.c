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

char *get_subshell_line(char *head)
{
	int i;
	char queue[100];

	i = 0;
	while (*head)
	{
		if (*head == ')' && i == 0)
			return (head);
		if (*head == '(')
			queue[i++] = '(';
		else if (*head == ')' && queue[(i) ? i - 1 : 0] == '(')
			i--;
		if (*head == '"' && queue[(i) ? i - 1 : 0] == '"')
			i--;
		else if(*head == '"' && queue[(i) ? i - 1 : 0] != '\'')
			queue[i++] = '"';
		if (*head == '\'' && queue[(i) ? i - 1 : 0] =='\'')
			i--;
		else if (*head == '\'' && queue[(i) ? i - 1 : 0] != '"')
			queue[i++] = '\'';
		if (*head == '\\')
			head++;
		head++;
	}
	return (NULL);
}

void	run_shell(char *line)
{
	t_token_list	*tokens;
	t_token			*head;

	(void)head;
	while (1)
	{
		if (ft_str_isnull(line) ||
			(tokens = handle_quote(&line, 1)) == NULL)
			break;
		head = tokens->head;
		shell(g_blt, &(get_t_line()->env), tokens);
		search_semi(g_blt, &(get_t_line()->env), tokens);
		//tokens->head = head;
		//free_token_list(tokens);
		break;
	}
}

int handle_subshell(char **ptr, t_string *str)
{
	char *tail;
	char *line;
	int pip[2];
	char *redirection;
	char c;

	if ((tail = get_subshell_line(*ptr + 2)) == NULL)
		return (0);
	line = ft_strndup(*ptr + 2, tail - (*ptr + 2));
	*ptr = tail + 1;
	pipe(pip);
	tail = ft_itoa(pip[1]);
	redirection = ft_strjoin(" >&", tail);
	line = ft_strjoin_free(line, redirection);
	run_shell(line);
	close(pip[1]);
	while (read(pip[0], &c, 1) > 0)
		push(str, c);
	str->string[--str->len] = '\0';
	free(tail);
	return (1);
}

int		handle_dollar(char **ptr, t_string *str)
{
	char	*head;
	char	*tmp;
	char	*env;
	t_list	*env_list;

	head = *ptr;
	if (*(++head) == '(')
		return handle_subshell(ptr, str);
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
