/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:04:22 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/22 12:12:54 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_redirect		*init_t_redirect(void)
{
	t_redirect		*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	redirect->command = NULL;
	redirect->dup_head = NULL;
	redirect->dup_tail = NULL;
	return (redirect);
}

t_duped			*init_t_duped(t_redirect *redirect)
{
	t_duped		*node;

	if ((node = (t_duped *)malloc(sizeof(t_duped))) == NULL)
		return (NULL);
	node->filed1 = -1;
	node->filed2 = -1;
	node->del = NULL;
	node->next = NULL;
	if (redirect->dup_head == NULL)
	{
		redirect->dup_head = node;
		redirect->dup_tail = node;
	}
	else
	{
		redirect->dup_tail->next = node;
		redirect->dup_tail = node;
	}
	return (node);
}

void			free_duped(t_redirect *redirect)
{
	t_duped		*duped;
	t_duped		*tmp;

	duped = redirect->dup_head;
	while (duped)
	{
		if (duped->filed1 > 2)
			close(duped->filed1);
		if (duped->filed2 > 2)
			close(duped->filed2);
		tmp = duped->next;
		free(duped->del);
		free(duped);
		duped = tmp;
	}
	ft_free_strtab(redirect->command);
	free(redirect);
}

int				loop_dup2(t_duped *current, int option)
{
	int flag;

	flag = 0;
	while (current)
	{
		if (option && current->filed2 == -2)
			return (1);
		else if (!option && current->filed2 == -2)
		{
			flag++;
			if (flag == 2)
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int				loop_dup(t_duped *current, int option)
{
	while (current)
	{
		if (option && current->filed2 >= 0 && current->filed1 == -4)
			exit(EXIT_FAILURE);
		else if (!option && current->filed2 >= 0 && current->filed1 == -4)
			return (0);
		if (current->filed1 != -1 && current->filed2 != -1
				&& current->filed1 != -5)
			dup2(current->filed1, current->filed2);
		else if (current->filed1 == -5)
			close(current->filed2);
		else
		{
			if (current->filed2 == -2)
				redirect_in_app(current->del, 0);
			else if (current->filed2 == -4)
				redirect_in_app(current->del, 1);
			current = current->next;
			continue;
		}
		current = current->next;
	}
	return (1);
}
