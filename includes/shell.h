/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 01:26:35 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/05 15:56:34 by amoutik          ###   ########.fr       */
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
# define BUF_S 10000
# define COPY_MAX 1000

//debug
#define TERM_TTY "/dev/ttys004"
void	debug_msg(char *msg, ...);


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
	char				copy[COPY_MAX];
	int					buf_size;
	int					top;
	int					index;
	int					current_index;
	t_list				*new_lines;
	t_list				*head_newlines;
	int					copy_mode;
	int					begin_copy;
	char				print_msg;
	t_list				**tail_history;
	t_list				*index_history;
	char				*tmp_history;
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
		char				*del;
		struct s_duped		*next;
}						t_duped;

typedef struct			s_redirect
{
		char				**command;
		struct s_duped		*dup_head;
		struct s_duped		*dup_tail;
}						t_redirect;

/*
**	minishell.c
*/
void					exec_cmd(t_command_list *command, char **path, t_list **env);
int						is_directory(const char *path);

/*
**	args.c
*/
int					fix_line(char **line, t_list *env);

/*
**	builtin.c
*/
void					free_builtin(t_list *lst);
void					init_builtin(t_list **lst);
int					check_builtin(t_list *elem, void *obj);
void					run_builtin(t_list **env, t_list *bltin, t_command_list *cmd);

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
**	read_line.c
*/
void					check_keys(int bif, t_line *line);
int						read_line(t_line *line);

/*
**	line.c
*/
t_line					*get_t_line(void);
void					free_line(void);
t_line					*init_line(void);
void					free_buffer(t_line *line);

/*
**	edit_line.c
*/
void					delete_char(t_line *line);
void					add_char(t_line *line, char c);
void					print_char_inline(t_line *line, int buf);
void					paste_chars(int *buf, t_line *line);

/*
**	terms.c
*/
struct termios			*get_termios(void);
int						init_termios(struct termios term);
int						init_terms(void);

/*
**	cursor.c
*/
void					go_left(t_line *line, int col);
void					go_right(t_line *line, int col);
void					move_cursor(int direction, t_line *line);

/*
**	cursor2.c
*/
int						get_current_row(int height);
void					go_down_left(void);
void					go_home(t_line *line, int col);
void					go_end(t_line *line, int col);

/*
**	cursor3.c
*/
void					go_up(t_line *line, int col);
void					go_down(t_line *line, int col);
void					next_word(t_line *line, int col, int direction);

/*
**	cursor4.c
*/
void					update_index(t_line *line, char step);
int						decision_up_right(t_line *line, int col);
int						decision_down_left(t_line *line, int col);
int						decision_top_down_left(t_line *line, int col);
void					set_new_current_index(t_line *line);
int						get_current_rows(t_line *line, int col);
void					update_newlines(t_line *line, char step);

/*
**	copy.c
*/
void					paste_text(t_line *line);
void					end_copy_mode(t_line *line, int keystrock);
void					begin_reset_mode(t_line *line);
void					go_left_copy_mode(t_line *line, int col);

/*
**	handlers.c
*/
void					child_handler(int sig);
void					signals(void);
void					exit_shell(char *format, ...);
void					syntax_error(t_duped *duped, char *format, ...);

/*
**	quotes.c
*/
void					push_stack(char *flag_quote, char buf);
int						check_stack(char flag_quote);

/*
**	pipe.c
*/
void					handle_piping(t_command_list *ptr, t_list **env, t_list *built_in);
int						is_piped(t_command_list *ptr);
void					execute_command(char ***cmd, t_list **env, t_list *built_in);

/*
** Path.c
*/
int						full_path(char **cmd, char **path_env);

/*
** redirection.c
*/

void					redirect_in_app(char *del, int option);
void					less_great(t_command **command, t_redirect *redirect);
void					less_and(t_command **command, t_redirect *redirect);
void					double_less(t_command **command, t_redirect *redirect);
void					jump_forward(t_command **command, t_duped *duped);
int						redir_out(char *filename, int perm);

/*
** quotes.c
*/
int						handle_dollar(char **line, char **new_line, int *i);
char					*remove_new_line(char *line, int len);
void					is_match(char spliter, t_line *current, t_command_list *command, char *start);
int						is_not_only_spaces(char *line);

/*
** quotes2.c
*/
void					handle_quote(t_line *current, t_command_list *command, char flag);


/*
** lists.c
*/
void					init_list(t_command_list *ptr);
void					push(t_command_list *ptr, char *command, int is_quoted);
void					free_list(t_command_list *ptr, int option);
void					print_list(t_command_list *ptr);
char					**list_to_chars(t_command_list *ptr);
t_command_list			*separated_by_del(t_command_list *ptr, char del);
char					*get_first_non_empty(t_command_list *ptr);

/*
**	tab.c
*/
void					handle_tab(t_line *line);

/*
**	history.c
*/
void					add_history(t_line *line);
void					handle_history(int buf, t_line *line);

/*
** tmp_redirect.c
*/
t_redirect				*handle_redirect(t_command_list *command);

/*
** t_redirect.c
*/
void					free_duped(t_redirect *redirect);
int						loop_dup(t_duped *current, int option);
int						loop_dup2(t_duped *current);
t_duped					*init_t_duped(t_redirect *redirect);
t_redirect				*init_t_redirect(void);

/*
**	paste.c
*/
void					paste_chars(int *buf, t_line *line);

/*
**  redirect1.c
*/

int						is_number(char *str);
int						redir_out(char *filename, int perm);
void					file_to_des(t_command **command, t_duped *duped, char *tmp, int perm);
void					file_or_fdes(t_command **command, t_duped *duped, char *tmp);
void					redirect_err_out(t_command **command, t_redirect *redirect);

/*
**	redirect2.c
*/

void					reverse_agregate(t_command **c, t_duped *d, char *t, t_redirect *r);
void					agregate_2_check(char *tmp, t_duped *duped, int num);
void					agregate_redirect(t_command **c, t_redirect *r);
void					simple_redirect(t_command **c, t_redirect *r);

/*
**	Pipe2.c
*/

void					piping(t_list *cmds, t_list **env, t_list *built_in);

/*
** quotes3.c
*/

int						handle_dollar(char **line, char **new_line, int *i);
t_command_list			*init_quotes(t_line *line, t_command_list *commands);
int						handle_tilda(char **line, char **new_line, int *i);

/*
** ft_asterisk
*/

void					handle_asterisk(t_command_list *command);
#endif
