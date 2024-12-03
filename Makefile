NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -Ilibft

LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

SRC = src/main.c \
	  src/lexer/lexer.c \
	  src/lexer/lexer_utils.c \
	  src/parser/parser.c \
	  src/parser/parser_utils.c

OBJECTS = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_LIB)

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

norm: 
	norminette $(SRC) minishell.h $(LIBFT_PATH)*.h $(LIBFT_PATH)*.c

.PHONY: all fclean clean re norm
