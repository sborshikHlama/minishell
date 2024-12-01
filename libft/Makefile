# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iasonov <iasonov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 22:56:57 by iasonov           #+#    #+#              #
#    Updated: 2024/12/01 22:25:28 by iasonov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		= cc
CFLAGS	= -Wall -Wextra -Werror -g
AR		= ar rcs
NAME	= libft.a
HEADER	= libft.h

SRC	=	ft_atoi.c		\
		ft_bzero.c		\
		ft_calloc.c		\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_isspace.c	\
		ft_itoa.c		\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_memcpy.c		\
		ft_memmove.c	\
		ft_memset.c		\
		ft_putchar_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\
		ft_putstr_fd.c	\
		ft_split.c		\
		ft_split_mult.c	\
		ft_strchr.c		\
		ft_strdup.c		\
		ft_strndup.c		\
		ft_striteri.c	\
		ft_strjoin.c	\
		ft_strlcat.c 	\
		ft_strlcpy.c	\
		ft_strlen.c 	\
		ft_strmapi.c	\
		ft_strncmp.c	\
		ft_strcmp.c	\
		ft_strnstr.c	\
		ft_strrchr.c	\
		ft_strtrim.c	\
		ft_substr.c		\
		ft_tolower.c	\
		ft_toupper.c	\
		gnl/gnl.c 		\
		gnl/gnl_utils.c	\
		hashmap/hashmap.c \

OBJS = $(SRC:.c=.o)

BONUS =	ft_lstadd_back_bonus.c	\
		ft_lstadd_front_bonus.c	\
		ft_lstclear_bonus.c		\
		ft_lstdelone_bonus.c	\
		ft_lstiter_bonus.c		\
		ft_lstlast_bonus.c		\
		ft_lstmap_bonus.c		\
		ft_lstnew_bonus.c		\
		ft_lstsize_bonus.c		\

BONUS_OBJS = $(BONUS:.c=.o)

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $(OBJS)  $(BONUS_OBJS)

.PHONY: all clean fclean re
