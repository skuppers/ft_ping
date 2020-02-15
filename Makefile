# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuppers <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/15 13:04:10 by skuppers          #+#    #+#              #
#    Updated: 2020/02/15 13:10:12 by skuppers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ping

SRC=src/main.c\
	src/ft_ping.c

OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRC)))))
CC=clang
CFLAGS=-Wall -Wextra #-Werror

all: $(NAME)

$(NAME): $(SRC)
	@cd lib; make
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) lib/libft.a

clean:
	@rm -f $(NAME)
