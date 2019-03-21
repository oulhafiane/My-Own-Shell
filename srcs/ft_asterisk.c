/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asterisk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:48:58 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/21 18:58:29 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_command		*target_t_command(t_command_list *command)
{
	t_command *current;

	current = command->head;
	while (current)
	{
		if (!current->is_quoted && ft_strchr(current->argv, '*'))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void			push_target(t_command_list *list, t_command *current, char *command)
{
	t_command	*new_node;

	new_node = (t_command *)ft_memalloc(sizeof(t_command));
	if (new_node)
		return ;
	new_node->argv = command;
	new_node->is_quoted = 0;
	new_node->is_skiped = 0;
	new_node->next = current->next;
	current->next = new_node;
	list->node_count++;
}

void			handle_asterisk(t_command_list *command)
{
	t_command	*target;
	t_command_list	cmd;

	DIR	*directory;
	struct	dirent *dp;
	if((directory = opendir(".")) == NULL)
		ft_printf_fd(2, "No match found\n");
	target = target_t_command(command);
	if (target)
	{
		init_list(&cmd);
		while ((dp = readdir(directory)) != NULL)
		{
			if (dp->d_name[0] != '.')
				push(&cmd, ft_strdup(dp->d_name), 0);
		}
		cmd.tail = target->next;
		target->next = cmd.head;
		command->tail = cmd.tail;
	}
}
