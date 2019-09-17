/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsignal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 10:37:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/17 19:42:51 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

char	*ft_getsigstr1_12(int sig)
{
	static char *str[13];

	if (!str[0])
	{
		ft_bzero(str, 13);
		str[0] = "+done";
		str[1] = "+hangup";
		str[2] = "-Interrupt";
		str[3] = "+Quit";
		str[4] = "+Illegal instruction";
		str[5] = "+trace trap";
		str[6] = "+abort";
		str[7] = "+EMT trap";
		str[8] = "+floating point exception";
		str[9] = "+killed";
		str[10] = "+bus error";
		str[11] = "+segmentation fault";
		str[12] = "+Bad system call";
	}
	if (sig >= 0 && sig <= 12)
		return (str[sig]);
	return (NULL);
}

char	*ft_getsigstr13_31(int sig)
{
	static char *str[19];

	if (!str[0])
	{
		ft_bzero(str, 19);
		str[1] = "-broken pipe";
		str[2] = "+Alarm clock";
		str[3] = "+terminated";
		str[4] = "+suspended (signal)";
		str[5] = "+suspended";
		str[8] = "+suspended (tty input)";
		str[9] = "+suspended (tty output)";
		str[11] = "+Cputime limit exceeded";
		str[12] = "+Filesize limit exceeded";
		str[13] = "+Virtual timer expired";
		str[14] = "+Profiling timer expired";
		str[17] = "+User defined signal 1";
		str[18] = "+User defined signal 2";
	}
	if (sig >= 13 && sig <= 31)
		return (str[sig - 12]);
	return (NULL);
}

char	*ft_strsignal(int sig)
{
	char	*str;

	if (sig <= 12)
		str = ft_getsigstr1_12(sig);
	else
		str = ft_getsigstr13_31(sig);
	if (str)
		return (str + 1);
	return (NULL);
}

void	ft_print_termsig(int status, char *name)
{
	int		sig;
	char	*msg;

	sig = WTERMSIG(status);
	msg = ft_strsignal(sig);
	if (msg && *(msg - 1) == '+')
		ft_printf("42sh : %s : %d \t %s\n", msg, sig, name);
}
