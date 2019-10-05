/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 18:50:18 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 14:49:09 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_free_lst(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	ft_free_redir(t_list *lst)
{
	t_redirect *rd;

	while (lst)
	{
		rd = lst->content;
		free(rd->file);
		lst = lst->next;
	}
}

void	ft_free_cmds(t_list *lst)
{
	t_command	*cmd;
	t_list		*head;

	head = lst;
	while (lst)
	{
		cmd = lst->content;
		free(cmd->heredoc);
		ft_free_array(cmd->argv);
		ft_free_redir(cmd->redirections);
		ft_free_lst(cmd->redirections);
		lst = lst->next;
	}
	ft_free_lst(head);
}
