/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:49:44 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/18 00:11:27 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H
# include <signal.h>
# include "libft.h"
# include "quote.h"
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# define RESET 1
# define GET_JOB 0
# define SILENT_MODE 1
# include <stdarg.h>

typedef struct			s_proc
{
	pid_t				pid;
	char				exited;
	char				stoped;
	char				wait;
	int					status;
	char				*name;
	char				waiting;
	char				signaled;
}						t_proc;

typedef struct termios	t_term;
typedef struct stat		t_stat;
typedef struct			s_job
{
	int			id;
	pid_t		pgid;
	t_list		*pids;
	char		*cmd;
	char		suspended;
	char		killed;
	char		foreground;
	t_term		term;
}						t_job;

typedef struct			s_container
{
	t_list	*list;
	t_job	*current;
	t_job	new;
	t_term	term;
	t_list	*notify;
	t_job	*last;
	int		last_status;
	char	time_to_exit;
}						t_container;

t_container				*ft_getset(t_container *container);
void					ft_fg(char **arg);
void					ft_bg(char **arg);
void					ft_jobs(void);
void					ft_init_jobcontrol();
void					ft_resetsignals();
void					ft_addjob(t_job *job, t_container *container);
void					ft_deljob(t_job *job, t_container *container);
void					ft_addprocess(t_job **job, pid_t pid, char wait);
void					ft_wait(t_job *job);
t_job					*ft_jobgetter(t_job *job, char reset);
void					ft_handle_jobs(t_token *token, pid_t pid, char *cmd);
void					ft_jobs_in_child(void);
t_job					*ft_newjob(t_token *token, pid_t pid,
							char *cmd, char wait);
t_job					*ft_getjob_byindex(int index);
void					ft_sort(t_list *list);
void					ft_sigchld(int sig);
void					ft_deljob(t_job *job, t_container *container);
t_job					*ft_getbypgid(t_list *list, pid_t pgid);
int						ft_isstopped(t_job	*job);
t_job					*ft_getjob(char **arg, char *caller);
void					ft_free_job(t_job *job);
void					restore_std(void);
char					*ft_join(char *f, ...);
void					ft_notify(void);
void					ft_init_wait(void);
t_proc					*ft_findjob(int pid);
t_proc					*ft_getproc_byjob(t_job *job, pid_t pid);
char					*ft_strsignal(int sig);
void					ft_print_termsig(int status, char *name);
char					ft_jobid_expansion(t_token *token);
void					ft_change_state(t_job *job, pid_t pid, int status);
int						ft_stoped(t_job *job);
int						ft_terminated(t_job *job);
void					ft_resetstatus(t_job *job);
void					ft_check_jobs_status(t_job *current);
#endif
