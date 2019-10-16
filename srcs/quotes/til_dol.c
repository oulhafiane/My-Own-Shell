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

void *ft_env_dup(t_list *node)
{
	t_env *env;
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	env = (t_env*)node->content;
	new->name = ft_strdup(env->name);
	new->value = ft_strdup(env->value);
	return (void *)new;
}

t_list *ft_map_lst(t_list *root, void *(*f)(t_list *node))
{
	t_list *lst;
	t_list *new;

	lst = NULL;
	if (root)
		lst = (t_list *)malloc(sizeof(t_list));
	new = lst;
	while (root)
	{
		lst->content = f(root);
		lst->next = NULL;
		if (root->next)
			lst->next = (t_list *)malloc(sizeof(t_list));
		root = root->next;
		lst = lst->next;
	}
	return new;
}

void	ft_env_del(void *content, size_t size)
{
	t_env *env;

	(void)size;
	env = (t_env *)content;
	free(env->name);
	free(env->value);
	free(env);
}

void	run_shell(char *line)
{
	t_token_list	*tokens;
	t_token			*head;
	t_list			*env;

	(void)head;
	env = ft_map_lst(get_t_line()->env, &ft_env_dup);
	while (1)
	{
		if (ft_str_isnull(line) ||
			(tokens = handle_quote(&line, 1)) == NULL)
			break;
		head = tokens->head;
		shell(g_blt, &env, tokens);
		search_semi(g_blt, &env, tokens);
		//tokens->head = head;
		//free_token_list(tokens);
		break;
	}
	ft_lstdel(&env, &ft_env_del);
}

char *clean_line(char **ptr, int out)
{
	char *tail;
	char *line;
	char *redirection;

	if ((tail = get_subshell_line(*ptr + 2)) == NULL)
		return (NULL);
	line = ft_strndup(*ptr + 2, tail - (*ptr + 2));
	*ptr = tail + 1;
	tail = ft_itoa(out);
	redirection = ft_strjoin(" >&", tail);
	free(tail);
	line = ft_strjoin_free(line, redirection);
	free(redirection);
	return line;
}

int handle_subshell(t_token_list *list, char **ptr)
{
	char *line;
	int pip[2];
	t_token	*token;
	t_token_list *tokens;

	pipe(pip);
	if ((line = clean_line(ptr, pip[1])) == NULL)
		return (0);
	run_shell(line);
	free(line);
	close(pip[1]);
	line = (char *)malloc(sizeof(char) * 65000);
	pip[1] = read(pip[0], line, 65000);
	line[pip[1] - 1] = '\0';
	token = list->head;
	while (token && token->next)
		token = token->next;
	tokens = handle_quote(&line, 1);
	(token) ? token -> next = tokens->head : 0;
	(!token) ? list->head = tokens->head : 0;
	list->tail =  tokens->tail;
	free(line);
	free(tokens);
	return (1);
}

int		handle_dollar(t_token_list *list, char **ptr, t_string *str)
{
	char	*head;
	char	*tmp;
	char	*env;
	t_list	*env_list;

	head = *ptr;
	if (*(++head) == '(')
		return handle_subshell(list, ptr);
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
