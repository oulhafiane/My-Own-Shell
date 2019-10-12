
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -c
SRCS = ft_lstnew.c     ft_putstr_fd.c  ft_strncat.c\
		ft_memalloc.c   ft_strcat.c     ft_strncmp.c\
		ft_atoi.c       ft_memccpy.c    ft_strchr.c     ft_strncpy.c\
		ft_bzero.c      ft_memchr.c     ft_strclr.c     ft_strnequ.c\
		ft_isalnum.c    ft_memcmp.c     ft_strcmp.c     ft_strnew.c\
		ft_isalpha.c    ft_memcpy.c     ft_strcpy.c     ft_strnlen.c\
		ft_isascii.c    ft_memdel.c     ft_strdel.c     ft_strnstr.c\
		ft_isspace.c    ft_memmove.c    ft_strdup.c     ft_strrchr.c\
		ft_isdigit.c    ft_memset.c     ft_strequ.c     ft_strsplit.c\
		ft_isprint.c    ft_putchar.c    ft_striter.c    ft_strstr.c\
		ft_itoa.c       ft_putchar_fd.c ft_striteri.c   ft_strsub.c\
		ft_lstadd.c     ft_putendl.c    ft_strjoin.c    ft_strtrim.c\
		ft_lstdel.c     ft_putendl_fd.c ft_strlcat.c    ft_tolower.c\
		ft_lstdelone.c  ft_putnbr.c     ft_strlen.c     ft_toupper.c\
		ft_lstiter.c    ft_putnbr_fd.c  ft_strmap.c  ft_strspn.c ft_strtok.c\
		ft_lstmap.c     ft_putstr.c     ft_strmapi.c ft_strcspn.c ft_abs.c ft_strjoin_free.c

HEADER = includes/libft.h
INC = includes
OBJECTS = $(SRCS:%.c=%.o)

all: $(NAME) $(HEADER)
	
$(NAME): $(OBJECTS) $(HEADER)
	@ar rc $(NAME) $(OBJECTS)

$(OBJECTS): $(SRCS) $(HEADER)
	@gcc $(CFLAGS) -I$(INC) $(SRCS)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

