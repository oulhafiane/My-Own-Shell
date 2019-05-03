/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 01:26:35 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/03 16:57:54 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "const.h"
# include "libft.h"
# include <dirent.h>
# include <term.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <string.h>
# define BUF_S 1000

typedef struct			s_builtin
{
	char				*cmd;
	void				(*f)();
}						t_builtin;

typedef struct			s_env
{
	char				*name;
	char				*value;
}						t_env;

typedef struct			s_line
{
	char				*command;
	char				*old_command;
	char				*copy;
	int					buf_size;
	int					col;
	int					top;
	int					index;
	int					current_index;
	t_list				*new_lines;
	t_list				*head_newlines;
	char				print_msg;
	t_list				**tail_history;
	t_list				*index_history;
	char				*tmp_history;
	t_list				*env;
}						t_line;

typedef struct			s_command
{
	char				*argv;
	int					is_quoted;
	int					is_skiped;
	struct s_command	*next;
}						t_command;

typedef struct			s_command_s
{
	struct s_command	*head;
	struct s_command	*tail;
	struct s_command	*index;
	int					node_count;
}						t_command_list;

typedef struct			s_duped
{
	int					filed1;
	int					filed2;
	int					closefd;
	char				*del;
	struct s_duped		*next;
}						t_duped;

typedef struct			s_redirect
{
	char				**command;
	struct s_duped		*dup_head;
	struct s_duped		*dup_tail;
}						t_redirect;

typedef struct			s_spliter
{
	char				spliter;
	char				*start;
	int					i;
	int					len;
}						t_spliter;

/*
**	=============================== MINISHELL ==================================
*/

/*
** main.c
*/
int						is_directory(const char *path);

/*
**	shell.c
*/
void					run_shell(t_list *builtin, t_line *line);

/*
**	builtin.c
*/
void					free_builtin(t_list *lst);
void					init_builtin(t_list **lst);
int						check_builtin(t_list *elem, void *obj);
void					run_builtin(t_list **env, t_list *bltin,
		t_command_list *cmd);

/*
**	env.c
*/
char					**get_path(t_list *env);
void					add_env(t_list **lst, char *name, char *value, int end);
void					init_env(t_list **lst, char **env);
char					**env_to_tab(t_list *lst);
void					free_env(t_list *lst);

/*
**	errors.c
*/
void					print_error(char *error, char *cmd);

/*
**	free.c
*/
void					free_elem_env(t_list *elem);
void					free_exec_cmd(char *error, char *full_path,
		char **head_path);

/*
**	ft_env.c
*/
char					*get_env_value(char *name, t_list *lst);

/*
**	builtins commands.
*/
void					ft_cd(char **args, t_list **env);
void					ft_echo(char **args, t_list **env);
void					ft_env(char **args, t_list **env);
void					ft_setenv(char **args, t_list **env);
void					ft_unsetenv(char **args, t_list **env);
void					ft_pwd(char **args, t_list **env);

/*
**	=============================== READLINE ==================================
*/

/*
**	copy.c
*/
void					handle_copy(t_line *line, int key);

/*
**	cursor.c
*/
void					go_left(t_line *line);
void					go_right(t_line *line);
void					move_cursor(int direction, t_line *line);

/*
**	cursor2.c
*/
int						get_current_row(int height);
void					go_home(t_line *line);
void					go_home_line(t_line *line);
void					go_end(t_line *line);
void					go_end_line(t_line *line);

/*
**	cursor3.c
*/
void					go_down(t_line *line);
void					go_up(t_line *line);
void					next_word(t_line *line, int direction);
void					update_line(t_line *line, char *tmp, char buf);

/*
**	cursor4.c
*/
void					update_index(t_line *line, char step);
int						decision_up_down(t_line *line);
int						get_current_rows(t_line *line);
int						decision_top_down_left(t_line *line, int current_rows);
void					set_new_current_index(t_line *line);

/*
**	edit_line.c
*/
void					print_newchar(t_line *line, int buf);
void					print_char_inline(t_line *line, int buf);
t_list					*free_next_newlines(t_line *line);
void					go_down_left(void);

/*
**	handlers.c
*/
void					child_handler(int sig);
void					signals(void);
void					exit_shell(char *format, ...);
void					syntax_error(t_duped *duped, char *format, ...);

/*
**	history.c
*/
void					handle_history(int buf, t_line *line);
void					add_history(t_line *line);

/*
**	line.c
*/
t_line					*get_t_line(void);
void					free_line(void);
t_line					*init_line(void);
void					handle_eot(t_line *line);

/*
**	paste.c
*/
void					print_pasted_chars(int *buf, t_line *line);
void					internal_paste(t_line *line);

/*
**	read_line.c
*/
void					clr_screen(int sig);
int						read_line(t_line *line);

/*
**	terms.c
*/
struct termios			*get_termios(void);
int						init_termios(struct termios term);
int						init_terms(void);

/*
**	=============================== PIPE ==================================
*/

/*
**	pipe.c
*/
void					execute_command(char ***cmd, t_list **env,
		t_list *built_in);
int						is_piped(t_command_list *ptr);
void					handle_piping(t_command_list *ptr, t_list **env,
		t_list *built_in);

/*
**	Pipe2.c
*/
void					piping(t_list *cmds, t_list **env, t_list *built_in);

/*
** Path.c
*/
int						full_path(char **cmd, char **path_env);

/*
**	============================= REDIRECTION ================================
*/

/*
** in_redirection.c
*/

void					redirect_in_app(char *del, int option, t_duped *);
void					less_great(t_command **command, t_redirect *redirect);
void					less_and(t_command **command, t_redirect *redirect);
void					double_less(t_command **command, t_redirect *redirect);

/*
** is_digit.c
*/
int						is_digit(char **tmp, t_duped *duped);

/*
** lists.c
*/
void					init_list(t_command_list *ptr);
void					push(t_command_list *ptr, char *command, int is_quoted);
void					free_list(t_command_list *ptr, int option);
char					**list_to_chars(t_command_list *ptr);
t_command_list			*separated_by_del(t_command_list *ptr, char del);

/*
** miscellaneous.c
*/
char					*get_first_non_empty(t_command_list *ptr);
void					free_line_assign(t_line **line);
void					jump_forward(t_command **command, t_duped *duped);
void					last_word(t_command_list *command,
		char **line, char **new_line, int *i);

/*
** redirect1.c
*/
int						is_number(char *str);
int						redir_out(char *filename, int perm);
void					file_to_des(t_command **command, t_duped *duped,
		char *tmp, int perm);
void					file_or_fdes(t_command **command, t_duped *duped,
		char *tmp);
void					redirect_err_out(t_command **command,
		t_redirect *redirect);

/*
** redirect2.c
*/
void					reverse_agregate(t_command **c, t_duped *d,
		char *t, t_redirect *r);
void					agregate_2_check(t_command **command,
		char *tmp, t_duped *duped, int num);
void					agregate_redirect(t_command **c, t_redirect *r);
void					simple_redirect(t_command **c, t_redirect *r);

/*
** redirect3.c
*/
t_redirect				*handle_redirect(t_command_list *command);

/*
** t_redirect.c
*/
t_redirect				*init_t_redirect(void);
t_duped					*init_t_duped(t_redirect *redirect);
void					free_duped(t_redirect *redirect);
int						loop_dup2(t_duped *current, int option);
int						loop_dup(t_duped *current, int option);

/*
**	=============================== QUOTES ==================================
*/

/*
** quotes.c
*/
char					*remove_new_line(char *line, int len);
void					is_match(char spliter, t_line *current,
		t_command_list *command, char *start);
int						is_not_only_spaces(char *line);

/*
** quotes2.c
*/
void					add_to_list(t_command_list *command,
						char *line, int *index, int is_quoted);
char					check_quote(char **line, char *spliter, char *start);
void					push_non_quoted(char *new_line, int *i,
		t_command_list *command);
void					init_var(t_line *current,
							char **line, char **start, char *spliter);

/*
** quotes3.c
*/
int						handle_dollar(char **line, char **new_line,
		t_list *env, t_spliter *spl);
int						handle_tilda(char **line, char **new_line,
		t_list *env, t_spliter *spl);
t_command_list			*init_quotes(t_line *line, t_command_list *commands);

/*
** quotes4.c
*/
void					handle_quote(t_line *current, t_command_list *command,
		char flag, t_list *env);

#endif
