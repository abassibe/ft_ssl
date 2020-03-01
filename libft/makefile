# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/13 02:07:34 by qumaujea          #+#    #+#              #
#    Updated: 2020/02/13 02:24:46 by qumaujea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	ft_bzero.c \
		ft_itoa_base_unsigned.c \
		ft_memalloc.c \
		ft_memcpy.c \
		ft_putendl.c \
		ft_putstr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_strfind.c \
		ft_strlen.c \
		ft_strnew.c \
		ft_ustrcpy.c \
		ft_ustrnew.c \
		exit_error.c

OBJS = $(SRCS:.c=.o)

SRCPATH = ./

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(addprefix $(SRCPATH), $(SRCS))
	@ar rc $(NAME) $(OBJS)

%.o: $(SRCPATH)%.c
	@gcc $(FLAGS) -c $< -I includes

.PHONY: all clean fclean re

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

