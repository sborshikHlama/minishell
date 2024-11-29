NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

SRC = src/main.c

OBJECTS = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_LIB)

$(OBJECTS): minishell.h

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

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
