/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:23:51 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/16 21:55:07 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXEC_H
# define FT_EXEC_H
# include "libft.h"
# define INTERN 1
# define ALIAS 2
# define COMMANDS 3
# define ANYHASH 4
# define INTERNV 5

typedef struct	s_map
{
	char	*key;
	char	*value;
	int		hits;
	char	type;
	char	exported;
}				t_map;

int		ft_redirect(int fdout, t_list *out);
void	ft_exec_job(t_params *params, t_list *lst);
int		ft_run(t_params *params, t_command *cmd);
int		ft_getfddst(char *token, char *next, char **file);
int		ft_getfdsrc(char **token, int type);
int		ft_gettype(char *str);
void	ft_getredirections(char *token, char *next, t_command *cmd);
void	ft_restorestd(char stdin, char stdout, char stderr, int pipfd);
void	ft_free_array(char **args);
void	ft_free_cmds(t_list *lst);
void	ft_free_lst(t_list *lst);
#endif