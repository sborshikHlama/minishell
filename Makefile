NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -Ilibft

LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

# Add the readline library
READLINE_LIB = -lreadline

SRC = src/main.c \
	  src/environ/environ.c \
	  src/environ/environ_utils.c \
	  src/lexer/lexer.c \
	  src/lexer/lexer_utils.c \
	  src/lexer/syntax_check.c \
	  src/parser/parser.c \
	  src/parser/parser_utils.c \
	  src/parser/env_expander.c \
	  src/parser/env_expander_utils.c \
	  src/print_debug/print_toklist.c \
	  src/print_debug/print_tree.c \
	  src/executor/executor.c \
	  src/executor/builtin_cd.c \
	  src/executor/builtin_pwd.c \
	  src/executor/builtin_echo.c \
	  src/executor/builtin_env.c \
	  src/executor/builtin_export.c \
	  src/executor/builtin_export_errors.c \
	  src/executor/builtin_unset.c \
	  src/executor/builtin_export_unset_utils.c \
	  src/executor/builtin_exit.c \
	  src/executor/executor_utils.c \
	  src/executor/pipe.c \
	  src/executor/redirection.c \
	  src/executor/heredoc.c \
	  src/signals/signals.c

OBJECTS = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_LIB) $(READLINE_LIB)

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

memleak: $(LIBFT_LIB) $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.supp -s ./$(NAME)

norm:
	norminette $(SRC) includes/minishell.h $(LIBFT_PATH)*.h $(LIBFT_PATH)*.c

.PHONY: all fclean clean re run memleak norm
