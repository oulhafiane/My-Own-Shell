/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:32:23 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/05/05 23:38:31 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H
# define M_ISDIR(m)	((m & 0170000) == 0040000)
# define TAB_KEY 9
# define CLR_KEY 12
# define UP_KEY 4283163
# define DOWN_KEY 4348699
# define RIGHT_KEY 4414235
# define LEFT_KEY 4479771
# define ESC_KEY 27
# define SPACE_KEY 32
# define RETURN_KEY 10
# define BACK_KEY 127
# define DEL_KEY 2117294875
# define HOME_KEY 4741915
# define HOME_LINE 1
# define END_KEY 4610843
# define END_LINE 5
# define EOT_KEY 4
# define GO_UP 1096489755
# define GO_DOWN 1113266971
# define GO_RIGHT 1130044187
# define GO_LEFT 1146821403
# define CTRL_SPACE 41154
# define ALT_LEFT 10783202
# define ALT_RIGHT 10848738
# define ALT_C 42947
# define CTRL_K 11
# define CTRL_U 21
# define CTRL_X 24
# define CTRL_V 10127586
# define MODE_CUT 0
# define MODE_COPY 1
# define NOTHING 0
# define CURSORON 1
# define SELECTED 2
# define MSG_PURE "$> "
# define MSG_QUOTE "> "
# define GET_MSG(x) x == 1 ? MSG_PURE : MSG_QUOTE
# define MSG "\033[32;1m" MSG_PURE "\033[0m"
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define DOLLAR_SIGN '$'
# define BACK_SLASH '\\'
# define ERROR_DIR 5
# define ECMD 3
# define EACCESS 2
# define EFILE 0
# define SUCCESS 1
# define STROUT 1
# define STRERR 2
# define STRAPP 4
# define STRIN 8
# define SPECIAL ";|"
# define OUTPUT_REDI '>'
# define INPUT_REDI '<'
# define DLESS "<<"
# define DGREAT ">>"
# define LESSAND "<&"
# define GREATAND ">&"
# define GREATAND_R "&>"
# define LESSGREAT "<>"
# define DLESSDASH "<<-"
# define AMPERSAND '&'
# define TILDA '~'
# define WRITE_END 1
# define READ_END 0
# define ERROR_MSG "21sh: syntax error near unexprected token"
# define FN_EXIST "No such file or directory"
# define SYNTAX_ERROR 101
# define PERM_DENIED 102
# define BAD_DESCRIPTOR 103
# define WHITESPACE ft_iswhitespace(*(*line))
# define END_OR_SEMI (!**line || **line == ';')
# define SPACE_OR_COMMA(line) (WHITESPACE || END_OR_SEMI)
# define QUOTE_S_D(line) (**line == SINGLE_QUOTE || **line == DOUBLE_QUOTE)
# define IS_CHAR *(*line -2 ) > 32 && *(*line - 2) <= '~'
# define FT_STRCHR !(IS_CHAR && !ft_strchr("<>", *(*line - 2)))
# define CONTAIN_S_D(line, start) (*line - 2) >= start && FT_STRCHR
# define RM_NEW_LINE(start) remove_new_line(ft_strdup(start), ft_strlen(start))
/*
** DOLAR CONDITION
*/
# define D_COND (spl->spliter != SINGLE_QUOTE && **line == DOLLAR_SIGN)
# define IS_BSLASH (*spliter == 0 && **line == BACK_SLASH)
# define IS_SINGLE_QUOTE (*spliter != DOUBLE_QUOTE && **line == SINGLE_QUOTE)
# define IS_DOUBLE_QUOTE (*spliter != SINGLE_QUOTE && **line == DOUBLE_QUOTE)

#endif
