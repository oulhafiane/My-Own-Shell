/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:54:52 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/04 16:55:43 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

#include "libft.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

# define DEBUG_TTY "/dev/ttys002"
# define EOS '\0'
# define SH_TOKEN "<>&|;"

/*! \enum token_type
 *
 *  It better to use enum to check word type
 */
enum token_type
{
	SH_WORD = 1,
	SH_PIPE = 2,
	SH_REDIRECTION = 4,
	SH_SEMI = 8,
	SH_QUOTED = 16,
	SH_DPIPE = 32
};

typedef struct  s_token
{
    char            *token;
    enum token_type tok_type;
    struct s_token  *next;
}               t_token;

typedef struct  s_token_list
{
    struct s_token     *head;
    struct s_token     *tail;
    int             node_count;
}               t_token_list; 

typedef struct s_string
{
    char *string;
    size_t cap;
    size_t len;
}             t_string;


/*
** Quote.c
*/

t_token_list    *handle_quote(char **line);
int				split_tok(t_token_list *list, char **ptr, t_string *str, enum token_type type);
void            new_string(t_string *str);
void            push(t_string *str, char c);
int				is_special_char(char c);

/*
** quote2.c
*/

int	          	insert_token(t_token_list *, t_string *, enum token_type);
int             split_quote(t_token_list *list, char **ptr, t_string *str, enum token_type type);
int             check_quote_ending(char **line);

/*
** til_dol.c
*/

int				handle_dollar(char **ptr, t_string *str);
int				handle_tilda(char **ptr, t_string *str);

/*
** debug.c
*/

void            debug_msg(const char *format, ...);

/*
** List.c
*/
void            init_token_list (t_token_list *list);
void            push_token(t_token_list *list, char *tok, enum token_type type);
void            print_tokens(t_token_list *list);
char			**list_to_chars(t_token_list *ptr);
void			free_token_list(t_token_list *list);
void			delete_token(t_token_list *list, t_token *tofind);

/*
** free_string.c
*/

void			free_token(t_token *node);
void            free_tokens(t_token_list *list);
void            free_string(t_string *);

/*
** err_number.c
*/

int             err_number();

#endif
