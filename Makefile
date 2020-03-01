# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/09 05:21:00 by abassibe          #+#    #+#              #
#    Updated: 2020/02/13 02:23:48 by qumaujea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRCS =	ft_ssl.c \
		md5.c \
		sha256.c \
		operations.c \
		input.c \
		select_hash_algo.c \
		get_input.c \
		print.c \
		md5_core.c \
		sha256_core.c

OBJS = $(SRCS:.c=.o)

SRCPATH = ./srcs/

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): libft.a $(OBJS) $(addprefix $(SRCPATH), $(SRCS))
	@gcc $(FLAGS) $(OBJS) -L. -lft -o $(NAME)

libft.a:
	@make -C libft/
	@mv libft/libft.a .
	@make clean -C libft/

%.o: $(SRCPATH)%.c
	@gcc $(FLAGS) -c $< -I includes

.PHONY: all clean fclean re

clean:
	@rm -f $(OBJS)
	@rm -f libft.a

fclean: clean
	@rm -f $(NAME)

re: fclean all

