/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:27:10 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/02/26 12:31:05 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list	**get_t_cmds(void)
{
	static t_list	*cmds = NULL;

	return (&cmds);
}

void	free_cmds(void)
{
	t_list	**cmds;
	//don't forget this
	(void)cmds;
}

void	add_new_cmd(void)
{
	t_list	**cmds;
	t_line	*new;

	cmds = get_t_cmds();
	new = (t_line*)ft_memalloc(sizeof(t_line));
	new->top = -1;
	new->index = -1;
	new->command = (char*)ft_memalloc(sizeof(char) * BUF_S);
	ft_lstadd_end(cmds, ft_lstnew(new, 0));
}

t_list	**init_cmds(void)
{
	t_list	**cmds;

	cmds = get_t_cmds();
	if (*cmds != NULL)
	{
		free_cmds();
		*cmds = NULL;
	}
	add_new_cmd();
	return (cmds);
}
