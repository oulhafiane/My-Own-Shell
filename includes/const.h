/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:32:23 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/20 12:38:11 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H
# define TAB_KEY 9
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
# define END_KEY 4610843
# define EOT_KEY 4
# define GO_UP 1096489755
# define GO_DOWN 1113266971
# define GO_RIGHT 1130044187
# define GO_LEFT 1146821403
# define CTRL_SPACE 41154
# define CTRL_X 8948194
# define CTRL_C 42947
# define CTRL_V 10127586
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
# define WRITE_END 1
# define READ_END 0
# define ERROR_MSG "21sh :syntax error near unexprected token"
# define FN_EXIST "No such file or directory\n"

#endif
