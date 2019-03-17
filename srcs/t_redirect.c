/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:04:22 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/17 15:41:01 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_duped(t_redirect *redirect)
{
	t_duped		*duped;
	t_duped		*tmp;

	duped = redirect->dup_head;

	while (duped)
	{
		tmp = duped->next;
		free(duped->del);
		free(duped);
		duped = tmp;
	}
	//Added
	ft_free_strtab(redirect->command);
	free(redirect);
	//
}

void	loop_dup(t_duped *current)
{
	while (current)
	{
		if (current->filed1 != -1 && current->filed2 != -1)
			dup2(current->filed1, current->filed2);
		else if (current->filed1 == -2)
			close(current->filed2);
		else if (current->filed2 == -2)
			redirect_in_app(current->del, 0);
		else if (current->filed2 == -4)
			redirect_in_app(current->del, 1);
		current = current->next;
	}
}
