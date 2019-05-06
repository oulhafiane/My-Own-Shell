/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:18:57 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/06 23:22:36 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

char	handle_redirection(t_token *token);
char	handle_left_redirect(t_token *token);
char	handle_right_redirect(t_token *token);

#endif
