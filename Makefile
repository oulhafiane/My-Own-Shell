NAME = 21sh

SRC = srcs
BIN = bin
INC = includes
LIB = libft
BUILT = builtin

SRC_MIN = $(wildcard $(SRC)/minishell/*.c)
SRC_PIP = $(wildcard $(SRC)/pipe/*.c)
SRC_QUO = $(wildcard $(SRC)/quotes/*.c)
SRC_REA = $(wildcard $(SRC)/readline/*.c)
SRC_RED = $(wildcard $(SRC)/redirection/*.c)

OBJ_MIN = $(patsubst %.c, %.o, $(SRC_MIN))
OBJ_PIP = $(patsubst %.c, %.o, $(SRC_PIP))
OBJ_QUO = $(patsubst %.c, %.o, $(SRC_QUO))
OBJ_REA = $(patsubst %.c, %.o, $(SRC_REA))
OBJ_RED = $(patsubst %.c, %.o, $(SRC_RED))

OBJECT = $(OBJ_MIN) $(OBJ_PIP) $(OBJ_QUO) $(OBJ_REA) $(OBJ_RED)
REAL_OBJECT = $(patsubst %, $(BIN)/%, /$(notdir $(OBJECT)))

CC = gcc
FLAGS = -g -Wall -Wextra -Werror
CPP_FLAGS = -I$(INC) -I$(LIB)/includes
LIBFT = $(LIB)/libft.a

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
NC = \033[1;0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECT)
	@echo "$(RED)Linking...$(NC)"
	@$(CC) $(REAL_OBJECT) -ltermcap -lreadline $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Finished...$(NC)"

$(LIBFT):
	@echo "$(BLUE)Getting Libraries...$(NC)"
	@make -C $(LIB)

%.o : %.c
	@mkdir -p $(BIN)
	@$(CC) $(FLAGS) $(CFLAGS) $(CPP_FLAGS) -c $< -o $(BIN)/$(notdir $@)

clean:
	@echo "$(RED)Cleaning up...$(NC)"
	@rm -rf $(REAL_OBJECT)
	@make -C $(LIB) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB) fclean

re : fclean all

.PHONY: all clean fclean re help

help :
	@echo "$(GREEN)src_minishell: $(RED)$(notdir $(SRC_MIN))$(NC)"
	@echo "$(GREEN)src_pipe: $(RED)$(notdir $(SRC_PIP))$(NC)"
	@echo "$(GREEN)src_quotes: $(RED)$(notdir $(SRC_QUO))$(NC)"
	@echo "$(GREEN)src_readline: $(RED)$(notdir $(SRC_REA))$(NC)"
	@echo "$(GREEN)src_redirect: $(RED)$(notdir $(SRC_RED))$(NC)"
	@echo "$(BLUE)obj: $(RED)$(notdir $(REAL_OBJECT)$(NC))"

valgrind :
	@valgrind --tool=memcheck --leak-check=full --track-origins=yes ./$(NAME)

val : $(NAME) valgrind

valre : re valgrind
