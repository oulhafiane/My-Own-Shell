/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:51:53 by amoutik           #+#    #+#             */
/*   Updated: 2019/05/04 09:09:47 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*get_first_non_empty(t_command_list *ptr)
{
	t_command	*current;

	current = ptr->head;
	while (current)
	{
		if (ft_strlen(current->argv) != 0 && !current->is_quoted)
			return (current->argv);
		else if (!ft_strlen(current->argv) && current->is_quoted)
			return (current->argv);
		current = current->next;
	}
	return (ptr->head->argv);
}

void			free_line_assign(t_line **line)
{
	free_line();
	init_line();
	(*line)->print_msg = 0;
	read_line(*line);
}

/*
** This function meant to jump one node forward
** To get the file name if it exists
*/

void			jump_forward(t_command **command, t_duped *duped)
{
	*command = (*command)->next;
	if (*command)
		(*command)->is_skiped = 1;
	if (*command && (*command)->argv && ft_strlen((*command)->argv))
		duped->del = ft_strdup((*command)->argv);
	else
	{
		duped->filed2 = 0;
		syntax_error(duped, "%s\n", ERROR_MSG);
	}
}

