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
	src/fqdn.c\
	src/options.c\
	src/interface.c\
	src/ft_ping.c\
	src/sockets.c\
	src/packet_builder.c\
	src/ipv4.c\
	src/tools.c\
	src/send_packet.c\
	src/checksum.c

INC=includes/

LIB=libft/

#OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRC)))))
CC=gcc
CFLAGS= -fsanitize=address -Wall -Wextra #-Werror

all: $(NAME)

$(NAME): $(SRC)
#	@cd lib; make
	@$(CC) $(CFLAGS) -o $(NAME) -I $(INC) -I $(LIB)/includes/ $(SRC) libft/libft.a

clean:
	@rm -f $(NAME)
