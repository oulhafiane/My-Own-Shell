/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asterisk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:48:58 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/22 18:53:38 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_command		*target_t_command(t_command_list *command, t_command **prev, t_command **next)
{
	t_command *current;

	if (*next == NULL)
		current = command->head;
	else
		current = *next;
	while (current)
	{
		if (!current->is_quoted && ft_strchr(current->argv, '*'))
		{
			*next = current->next;
			return (current);
		}
		*prev = current;
		current = current->next;
	}
	*next = NULL;
	return (NULL);
}

void			change_node(t_command_list *command, t_command **prev, t_command_list *cmd, t_command **target)
{
	t_command	*tmp;

	tmp = cmd->tail;
	(*prev)->next = cmd->head;
	cmd->tail = (*target)->next;
	command->tail = cmd->tail;
	*prev = tmp;
	free((*target)->argv);
	free(*target);
}

void			handle_asterisk(t_command_list *command)
{
	t_command	*target;
	t_command_list	cmd;
	t_command	*prev;
	t_command	*next;

	prev = NULL;
	next = NULL;
	DIR	*directory;
	struct	dirent *dp;
	while (1)
	{
		if((directory = opendir(".")) == NULL)
			ft_printf_fd(2, "No match found\n");
		target = target_t_command(command, &prev, &next);
		if (target)
		{
			init_list(&cmd);
			while ((dp = readdir(directory)) != NULL)
			{
				if (dp->d_name[0] != '.')
					push(&cmd, ft_strdup(dp->d_name), 1);
			}
			change_node(command, &prev, &cmd, &target);
		}
		else
			break;
		closedir(directory);
	}
}
