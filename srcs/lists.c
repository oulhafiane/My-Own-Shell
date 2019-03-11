/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:57:32 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/11 15:17:38 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_list(t_command_list *listptr)
{
	listptr->head = NULL;
	listptr->tail = NULL;
	listptr->node_count = 0;
}

void	push(t_command_list *listptr, char *command)
{
	t_command *new_node_ptr;

	new_node_ptr = (t_command *)malloc(sizeof(t_command));
	if (new_node_ptr == NULL)
		return ;
	new_node_ptr->argv = command;
	new_node_ptr->next = NULL;
	if (listptr->node_count == 0)
	{
		listptr->head = new_node_ptr;
		listptr->tail = new_node_ptr;
	}
	else
	{
		listptr->tail->next = new_node_ptr;
		listptr->tail = new_node_ptr;
	}
	listptr->node_count++;
}

void	free_list(t_command_list *ptr)
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
	init_list(ptr);
}

void		print_list(t_command_list *ptr)
{
	t_command *head;

	head = ptr->head;
	while (head)
	{
		ft_printf("%s\n", head->argv);
		head = head->next;
	}
}
/*
char		**list_to_chars(t_command_list *ptr)
{
	
}*/
