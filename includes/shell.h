/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 01:26:35 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/10/05 21:22:48 by sid-bell         ###   ########.fr       */
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
# include <glob.h>
# include "jobcontrol.h"
# include "exec.h"
# define COUNT 1500
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

t_list *g_blt;

/*
**	=============================== MINISHELL ==================================
*/

/*
**	shell.c
*/
int						search_semi(t_list *blt, t_list **env, t_token_list *tokens);
void					shell(t_list *blt, t_list **env, t_token_list *tokens);

/*
**	builtin.c
*/
void					init_builtin(t_list **lst);
int						check_builtin(t_list *elem, void *obj);
void					free_builtin(t_list *lst);
void					run_builtin(t_params *params, void (*f)(), char **cmds, t_token_list *tokens);

/*
**	env.c
*/
char					**get_path(t_list *env);
void					add_env(t_list **lst, char *name, char *value, int end);
void					init_env(t_list **lst, char **env);
char					**env_to_tab(t_list *lst);
void					free_env(t_list *lst);

/*
**	free.c
*/
void					free_exec_cmd(char *error, char *full_path,
		char **head_path);
void					free_elem_env(t_list *elem);

/*
**	ft_env.c
*/
char					*get_env_value(char *name, t_list *lst);

/*
**	builtins commands.
*/
void					ft_cd(char **args, t_params *params);
void					ft_echo(char **args);
void					ft_env(void);
void					ft_setenv(char **args);
void					ft_unset(char **args);

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
void					decision_top_down_left(t_line *line, int current_rows);
void					set_new_current_index(t_line *line);

/*
**	edit_line.c
*/
void					print_newchar(t_line *line, int buf);
t_list					*free_next_newlines(t_line *line);
void					print_char_inline(t_line *line, int buf);
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
**	tab.c
*/
int						get_next_tabs(t_line *line);
int						get_previous_tabs(t_line *line);
void					move_left_tab(t_line *line);
void					add_tab(t_line *line);
void					print_current_tab(t_line *line);


void					exec_cmd(t_token *token, char **path, t_list **env,
								int std[2]);
void					ft_exit(char **argv, t_params *params);
void					ft_exec(t_list *blt, t_list **env,
								t_token *node, int std[2]);
void					ft_init_run_builtin(t_list **env,
							t_list *bltin, t_token *node, int std[2]);
t_builtin				*ft_is_builtin(char *cmd, t_list *blt);
char					*getpath(char *cmd, char **path);
char					ft_isnumber(char *str);
void					ft_fork(t_params *params, char *file,
							t_command *cmd, t_builtin *blt);
void					ft_alias(char **args);
void					ft_unalias(char **cmd);
t_map					*ft_get_alias(char *key, t_list *list);
void					ft_show_aliases(char *key);
void					ft_free_aliases(void);
void					ft_hash();
void					ft_init_hash(t_list *env);
void					ft_load(void);
char					*ft_getvlaue_bykey(char *key, char type);
void					ft_type(char **args);
t_map					*ft_getbykey(char *key, char type);
t_map					*ft_addtohashmap(char *key, char *value, char type);
void					ft_empty(char freeall);
int						ft_hash_calc(char *key);
void					ft_hashdelete_one(char *key, char type);
void					ft_get_kv(char *str, char **key, char **val);
void					ft_addexported(t_list **env, char *key, char *val);
void					ft_export(char **args);
void					ft_print_hash_list(void);
char					ft_isintern(char *cmd);
t_list					*ft_cpyenv(void);
int						ft_getinterns(t_params *params, t_command *cmd);
void					ft_set(void);
void					ft_insert_at(t_token_list *tokens, t_token *new, int index);
char					*ft_findfile(char *name, char **error);
#endif
