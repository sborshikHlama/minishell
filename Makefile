NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -Ilibft

LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

# Add the readline library
READLINE_LIB = -lreadline
READLINE_FLAGS = -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

SRC = src/main.c \
	  src/lexer/lexer.c \
	  src/lexer/lexer_utils.c \
	  src/parser/parser.c \
	  src/parser/parser_utils.c \
	  src/print_debug/print_toklist.c \
	  src/print_debug/print_tree.c \
	  src/executor/executor.c \
	  src/executor/builtin_cd.c \
	  src/executor/builtin_pwd.c \
	  src/executor/builtin_echo.c \
	  src/executor/builtin_env.c \
	  src/executor/executor_utils.c

OBJECTS = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(READLINE_FLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_LIB) $(READLINE_LIB)

$(OBJECTS): includes/minishell.h

$(LIBFT_LIB):
	make bonus -C $(LIBFT_PATH)

clean:
	rm -f $(OBJECTS)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all

run: $(LIBFT_LIB) $(NAME)
	./$(NAME)

norm: 
	norminette $(SRC) includes/minishell.h $(LIBFT_PATH)*.h $(LIBFT_PATH)*.c

.PHONY: all fclean clean re norm
