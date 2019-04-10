/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:51:53 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/10 20:52:59 by amoutik          ###   ########.fr       */
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
