/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:49:44 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/05 20:24:50 by sid-bell         ###   ########.fr       */
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
# define APPEND (O_WRONLY|O_CREAT|O_APPEND)
# define TRUNC (O_WRONLY|O_CREAT|O_TRUNC)
# define CLOSE_FD -2
# define HERDOC -1
# include <stdarg.h>

typedef struct			s_line
{
	char				*command;
	char				*copy;
	int					buf_size;
	int					col;
	int					top;
	int					index;
	int					current_index;
	t_list				*new_lines;
	t_list				*head_newlines;
	int					total_tabs;
	int					count_down;
	int					current_row;
	char				print_msg;
	t_list				**tail_history;
	t_list				*index_history;
	char				*tmp_history;
	t_list				*env;
	t_list				*intern;
}						t_line;

typedef struct			s_proc
{
	pid_t				pid;
	char				exited;
	char				stoped;
	int					status;
	char				*name;
	char				signaled;
}						t_proc;

typedef struct termios	t_term;
typedef struct stat		t_stat;
typedef struct			s_job
{
	int				id;
	pid_t			pgid;
	t_list			*pids;
	char			*cmd;
	char			suspended;
	char			killed;
	char			foreground;
	t_term			term;
	t_token_list	*tokens;
	char			notified;
}						t_job;

typedef struct			s_container
{
	t_list			*list;
	t_job			*current;
	t_job			new;
	t_term			term;
	t_list			*notify;
	t_job			*last;
	int				last_status;
	t_list			*builtins;
	t_line			*line;
	char			interractive;
	char			time_to_exit;
	int				stdcopy;
	t_list			*last_aliases;
	t_list			**hashmap;
	t_list			*env;
}						t_container;

typedef struct			s_redirect
{
	char			*file;
	int				fd_src;
	int				fd_dst;
	int				mode;
	char			ambiguous;
	t_list			*redirections;
}						t_redirect;

typedef struct			s_command
{
	char			**argv;
	char			*heredoc;
	t_list			*redirections;
	int				herdocfd;
}						t_command;

typedef struct			s_params
{
	t_list			*commands;
	t_token_list	*tokens;
	int				forkforbuiltin;
	int				fd;
	int				argv_index;
	int				pipe_stdin;
	t_list			*tmpenv;
}						t_params;

t_container				*ft_getset(t_container *container);
void					ft_fg(char **arg);
void					ft_bg(char **arg);
void					ft_jobs(void);
void					ft_init_jobcontrol();
void					ft_resetsignals();
void					ft_addjob(t_job *job, t_container *container);
void					ft_deljob(t_job *job, t_container *container);
void					ft_addprocess(t_job **job, pid_t pid);
void					ft_wait(t_job *job);
t_job					*ft_jobgetter(t_job *job, char reset);
void					ft_handle_jobs(t_token_list *tokens, pid_t pid);
void					ft_jobs_in_child(void);
t_job					*ft_newjob(t_token_list *tokens, pid_t pid);
t_job					*ft_getjob_byindex(int index);
void					ft_sort(t_list *list);
void					ft_sigchld(int sig);
void					ft_deljob(t_job *job, t_container *container);
t_job					*ft_getbypgid(t_list *list, pid_t pgid);
int						ft_isstopped(t_job	*job);
t_job					*ft_getjob(char **arg, char *caller);
void					ft_free_job(t_job *job);
void					ft_reset2(int all);
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
void					ft_set_last_rvalue(int rvalue);
int						ft_get_last_rvalue(void);
void					ft_expand_last_status(t_token *token);
void					ft_exec_mode(t_token *token, char *forgrounded);
void					pre_run(t_list *blt, t_list **env, t_token_list *tokens);
void					ft_runnext(t_token_list *tokens, int status);
void					next_and_or(t_token_list *tokens);
int						check_and_or(t_token *token);
void					ft_exec_mode(t_token *token, char *forgrounded);
void					ft_convert(t_token *node, t_params *params);
void					ft_ignore_signlas(void);
t_job					*ft_pid_lookup(pid_t pid, t_proc **procc);
char					ft_isjobseperator(enum e_token_type type);
#endif
