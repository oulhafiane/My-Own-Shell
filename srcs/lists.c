/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:57:32 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/13 15:51:36 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_list(t_command_list *listptr)
{
	listptr->head = NULL;
	listptr->tail = NULL;
	listptr->index = NULL;
	listptr->node_count = 0;
}

void	push(t_command_list *listptr, char *command, int is_quoted)
{
	t_command *new_node_ptr;

	new_node_ptr = (t_command *)ft_memalloc(sizeof(t_command));
	if (new_node_ptr == NULL)
		return ;
	new_node_ptr->argv = command;
	new_node_ptr->is_quoted = is_quoted;
	new_node_ptr->next = NULL;
	if (listptr->node_count == 0)
	{
		listptr->head = new_node_ptr;
		listptr->index = new_node_ptr;
		listptr->tail = new_node_ptr;
	}
	else
	{
		listptr->tail->next = new_node_ptr;
		listptr->tail = new_node_ptr;
	}
	listptr->node_count++;
}

/*
** The option param intention is to decide whether to free
** The whole list or not if it's allocated
*/

void	free_list(t_command_list *ptr, int option)
{
	t_command	*head;
	t_command	*tmp;

	head = ptr->head;
	while (head)
	{
		tmp = head->next;
		free(head->argv);
		free(head);
		head = tmp;
	}
	if (option == 1)
		free(ptr);
	else
		init_list(ptr);
}

void		print_list(t_command_list *ptr)
{
	t_command *current;

	current = ptr->head;
	while (current)
	{
		ft_printf("|%s|\n", current->argv);
		current = current->next;
	}
}

char		**list_to_chars(t_command_list *ptr)
{
	char		**cmds;
	t_command	*node;
	int			i;

	cmds = (char**)ft_memalloc(sizeof(char*) * (ptr->node_count + 1));
	node = ptr->head;
	i = 0;
	while (node)
	{
		if (node->is_quoted == 0 && is_only_spaces(node->argv))
			cmds[i++] = ft_strdup(node->argv);
		node = node->next;
	}
	cmds[i] = NULL;
	return (cmds);
}

t_command_list	*separated_by_del(t_command_list *ptr, char del)
{
	t_command_list	*commands;
	t_command		*current;

	if((commands = (t_command_list *)malloc(sizeof(t_command_list))) == NULL)
		return (NULL);
	init_list(commands);
	current = ptr->head;
	while (current && current != ptr->index)
		current	= current->next;
	while (current)
	{
		if (*current->argv == del && ft_strlen(current->argv) == 1)
		{
			ptr->index = current->next;
			break;
		}
		push(commands, current->argv, current->is_quoted);
		current = current->next;
	}
	if (current == NULL)
		ptr->index = NULL;
	return (commands);
}
