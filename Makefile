NAME = 21sh

SRC = srcs
BIN = bin
INC = includes
LIB = lib
BUILT = builtin

SOURCE = $(wildcard $(SRC)/*.c)
OBJECT = $(patsubst %, $(BIN)/%, $(notdir $(SOURCE:.c=.o)))

CC = gcc
FLAGS = -g -Wall -Wextra -Werror
CPP_FLAGS = -I$(INC) -I$(LIB)/libft/includes
LIBFT = $(LIB)/libft/libft.a

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
NC = \033[1;0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECT)
	@echo "$(RED)Linking...$(NC)"
	@$(CC) $(OBJECT) -ltermcap $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Finished...$(NC)"

$(LIBFT):
	@echo "$(BLUE)Getting Libraries...$(NC)"
	@make -C $(LIB)/libft

$(BIN)/%.o : $(SRC)/%.c
	@$(CC) $(FLAGS) $(CFLAGS) $(CPP_FLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning up...$(NC)"
	@rm -rf $(OBJECT)
	@make -C $(LIB)/libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB)/libft fclean

re : fclean all

.PHONY: all clean fclean re help

help :
	@echo "src: $(SOURCE)"
	@echo "obj: $(OBJECT)"

valgrind :
	@valgrind --tool=memcheck --leak-check=full --track-origins=yes ./$(NAME)

val : valgrind
