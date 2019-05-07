/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 01:26:35 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/07 03:04:50 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "const.h"
# include "libft.h"
# include "quote.h"
# include "redirection.h"
# include <dirent.h>
# include <term.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <string.h>
# include <glob.h>
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

/*
**	=============================== MINISHELL ==================================
*/

/*
**	shell.c
*/
void					shell(t_list *blt, t_list **env, t_token_list *tokens); 

/*
** fork.c
*/
void					next_pipe(t_token_list *tokens);
char					check_pipe(t_token *token);
void					forkit(char *path, t_list **env, t_token *token,
		int pipe[2]);


/*
**	builtin.c
*/
void					free_builtin(t_list *lst);
void					init_builtin(t_list **lst);
int						check_builtin(t_list *elem, void *obj);
void					run_builtin(t_list **env, t_list *bltin,
		t_token *node, int std[2]);

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

/*
**	history.c
*/
void					handle_history(int buf, t_line *line);
void					add_history(t_line *line);

/*
**	line.c
*/
t_line					*get_t_line(void);
int						my_putchar(int c);
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
**	tabulation.c
*/

void					handle_tabulation(t_line *line);

#endif
