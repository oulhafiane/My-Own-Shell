/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getredirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:17:57 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/02 15:01:32 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_redirect	*ft_addredirect(t_command *cmd, int fdsrc, int fddst, char *file)
{
	t_redirect	*red;
	t_list		*node;

	red = malloc(sizeof(t_redirect));
	red->fd_dst = fddst;
	red->fd_src = fdsrc;
	red->file = file ? ft_strdup(file) : NULL;
	red->ambiguous = fdsrc != 1 && fddst == -3 && file;
	node = ft_lstnew(red, 0);
	ft_lstadd(&cmd->redirections, node);
	return (red);
}

char		ft_getheredoc(int type, t_command *cmd, char *next, int fdsrc)
{
	if (type == HERDOC)
	{
		cmd->heredoc = ft_strdup(next);
		cmd->herdocfd = fdsrc;
		return (1);
	}
	return (0);
}

void		ft_getredirections(char *token, char *next, t_command *cmd)
{
	int			fdsrc;
	int			fddst;
	int			type;
	char		*file;
	t_redirect	*red;

	file = NULL;
	type = ft_gettype(token);
	fdsrc = ft_getfdsrc(&token, type);
	if (ft_getheredoc(type, cmd, next, fdsrc))
		return ;
	fddst = ft_getfddst(token, next, &file);
	if (fdsrc == -1)
	{
		fdsrc = 2;
		red = ft_addredirect(cmd, fdsrc, fddst, file);
		red->ambiguous = 0;
		red->mode = type;
		fdsrc = 1;
	}
	red = ft_addredirect(cmd, fdsrc, fddst, file);
	red->mode = type;
	red->ambiguous = (type == O_RDONLY && fddst == -3 && file)
			? 1 : red->ambiguous;
}
