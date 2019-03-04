/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 09:39:05 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/04 09:44:40 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** File name to redirect from
*/

void	redirect_in(char *filename)
{
	int fd_in;

	fd_in = open(filename, O_RDONLY);
	if (fd_in != -1 && dup2(fd_in, 0) != -1)
		close(fd_in);
}

/*
**	File name to redirect to
*/

void	redirect_out(char *filename, int fd, int permission)
{
	int fd_out;

	fd_out = open(filename, permission | O_CREAT, 0644);
	if (fd_out != -1 && dup2(fd_out, fd) != -1)
		close(fd_out);
}

/*
** Get the input from the strin
*/

void	redirect_in_app(char *del)
{
	int		fd[2];
	int		ret;
	char	buf[BUF_S];

	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	ft_printf_fd(2, "> ");
	while ((ret = read(0, buf, BUF_S)) > 0)
	{
		buf[ret] = '\0';
		if (ft_strncmp(buf, del, ret - 1) == 0)
			break ;
		ft_printf_fd(fd[1], "%s", buf);
		ft_printf_fd(2, "> ");
	}
	close(fd[1]);
	dup2(fd[0], 0);
}

/*
** Check if it is a redirection or not
*/

int		is_redirection(char *str, int *flag)
{
	int		is_quoted;
	char	*ptr;
	int		len;

	is_quoted = (str != NULL && ((str[0] == '\"' || str[0] == '\''))) ? 1 : 0;
	if (!is_quoted && (ptr = ft_strchr(str, '>')))
	{
		len = ft_strlen(str);
		if ((len == 1 && ft_strcmp(str, ">") == 0) ||
				(ptr > str && *(ptr - 1) == '1' && *(ptr + 1) == '\0'))
			*flag |= STROUT;
		else if (ptr > str && *(ptr - 1) == '2' && *(ptr + 1) == '\0')
			*flag |= STRERR;
		else if (ptr == str && *(ptr + 1) == '>' && *(ptr + 2) == '\0')
			*flag |= STRAPP;
		else if (ptr > str && *(ptr - 1) == '2' && *(ptr + 1) == '>')
			*flag |= (STRERR | STRAPP);
		else if ((len == 2 && str[0] == '&' && str[1] == '>') ||
				(len == 4 && *(ptr - 1) == '2' && *(ptr + 1) == '&' &&
				*(ptr + 2) == '1'))
			*flag |= (STRERR | STROUT);
		else if (len == 4 && *(ptr - 1) - '0' >= 0 &&
				*(ptr - 1) - '0' <= 2 && *(ptr + 2) == '-')
			close(*(ptr - 1) - '0');
	}
	return (*flag);
}

int		is_redirection_in(char *str, int *flag)
{
	char	*ptr;
	char	is_quoted;
	int		len;

	is_quoted = (str != NULL && ((str[0] == '\"' || str[0] == '\''))) ? 1 : 0;
	if (!is_quoted && (ptr = ft_strchr(str, '<')))
	{
		len = ft_strlen(str);
		if (len == 1 && ft_strcmp(str, "<") == 0)
			*flag |= STRIN;
		if (len == 2 && ft_strcmp(str, "<<") == 0)
			*flag |= (STRIN | STRAPP);
		if (len == 4)
			if (*str >= '0' && *str <= '9' && *(str + 1) == '<' &&
					*(str + 2) == '&' && *(str + 3) >= '0' && *(str + 3) <= '9')
				if (dup2(*(str + 3) - 0, *str - '0') == -1)
					*flag |= STRIN;
		if (len == 2 && ft_strcmp(str, "<&") == 0)
		{
			ft_printf("21sh: file number expected\n");
			exit(EXIT_FAILURE);
		}
	}
	return (*flag);
}

void	handle_flags(int flag, int flag_in, char *filename_in, char *filename)
{
	if (flag != 0)
	{
		if ((flag & ~STROUT) == 0)
			redirect_out(filename, 1, O_WRONLY | O_TRUNC);
		else if ((flag & ~STRERR) == 0)
			redirect_out(filename, 2, O_WRONLY | O_TRUNC);
		else if ((flag & ~STRAPP) == 0)
			redirect_out(filename, 1, O_WRONLY | O_APPEND);
		else if ((flag & ~(STRERR | STRAPP)) == 0)
			redirect_out(filename, 2, O_WRONLY | O_APPEND);
		else if ((flag & ~(STRERR | STROUT)) == 0)
		{
			redirect_out(filename, 2, O_WRONLY | O_TRUNC);
			dup2(2, 1);
		}
	}
	if (flag_in == 0)
		return ;
	if (flag_in != 0 && (flag_in & ~STRIN) == 0)
		redirect_in(filename_in);
	else if (flag_in != 0 && (flag_in & ~(STRIN | STRAPP)) == 0)
		redirect_in_app(filename_in);
}

/*
** Loop throughout the command list arguments \
** and see if there are any redirections or not
*/

void	handle_redirection(char ***in)
{
	int		flag;
	int		flag_in;
	char	*filename_in;
	char	*filename;
	char	**cmd;

	flag = 0;
	flag_in = 0;
	cmd = *in;
	filename = NULL;
	filename_in = NULL;
	while (*cmd)
	{
		if ((is_redirection(*cmd, &flag)) >= 1 ||
				(is_redirection_in(*cmd, &flag_in)) >= 1)
		{
			if (*(cmd + 1) != NULL)
			{
				*cmd = NULL;
				if (flag != 0 && filename == NULL)
					filename = *(cmd + 1);
				else if (flag_in != 0 && filename_in == NULL)
					filename_in = *(cmd + 1);
			}
		}
		cmd++;
	}
	handle_flags(flag, flag_in, filename_in, filename);
}
