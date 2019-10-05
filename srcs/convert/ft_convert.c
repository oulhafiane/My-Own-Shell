/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 15:28:16 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/30 17:52:09 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		ft_isnumber(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

t_command	*ft_newcmd(t_token *token)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->argv = list_to_chars(token);
	cmd->heredoc = NULL;
	cmd->redirections = NULL;
	return (cmd);
}

void		ft_addcmd(t_command *cmd, t_params *params)
{
	t_list		*node;

	node = ft_lstnew(cmd, 0);
	ft_lstadd(&params->commands, node);
}

void		ft_revers(t_list *lst)
{
	t_command *cmd;

	while (lst)
	{
		cmd = lst->content;
		if (cmd->redirections)
			ft_lstrev(&cmd->redirections);
		lst = lst->next;
	}
}

void		ft_convert(t_token *node, t_params *params)
{
	t_command	*cmd;

	cmd = ft_newcmd(node);
	ft_addcmd(cmd, params);
	while (node)
	{
		if (node->tok_type & SH_PIPE)
		{
			node = node->next;
			cmd = ft_newcmd(node);
			ft_addcmd(cmd, params);
		}
		if ((node->tok_type & SH_SEMI) || (node->tok_type & SH_DPIPE
			|| node->tok_type & SH_LOGAND || node->tok_type & SH_IMPER))
			break ;
		if (node->tok_type & SH_REDIRECTION)
		{
			ft_getredirections(node->token, node->next->token, cmd);
			if (!(node = node->next))
				break ;
		}
		node = node->next;
	}
	ft_revers(params->commands);
	ft_lstrev(&params->commands);
}
