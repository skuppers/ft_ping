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

#---------------------------------- GENERAL -----------------------------------#

NAME=ft_ping
DEBUG_NAME=ft_pingdbg

CC=clang

PATH_LIB=libft/

LIBFT= $(PATH_LIB)libft.a


CFLAGS += -Wall
CFLAGS += -Wextra
#CFLAGS += -Werror

DBFLAGS += $(CFLAGS)
DBFLAGS += -fsanitize=address,undefined
DBFLAGS += -ggdb3

#---------------------------------- INCLUDES ----------------------------------#

INCLUDES_LIBFT = $(PATH_LIB)includes/
INCLUDES_PING = includes/

I_INCLUDES += -I $(INCLUDES_LIBFT)
I_INCLUDES += -I $(INCLUDES_PING)

#---------------------------------- HEADERS -----------------------------------#

vpath %.h $(INCLUDES_LIBFT)
vpath %.h $(INCLUDES_PING)

HEADER += libft.h
HEADER += ft_ping.h

#----------------------------------- SOURCS -----------------------------------#

PATH_SRCS = src/

SRCS += main.c
SRCS += resolve.c
SRCS += options.c
SRCS += ft_ping.c
SRCS += sockets.c
SRCS += packet_builder.c
SRCS += ipv4.c
SRCS += tools.c
SRCS += send_packet.c
SRCS += checksum.c
SRCS += receive_packet.c
SRCS += display.c
SRCS += init.c
SRCS += error.c
SRCS += signals.c
SRCS += usage.c
SRCS += statistics.c
SRCS += response_codes.c
SRCS += listutils.c

vpath %.c $(PATH_SRCS)

#----------------------------------- OBJECTS ----------------------------------#

PATH_OBJS = objs/
OBJS = $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

DEBUG_PATH_OBJS = objs_debug/
DEBUG_OBJS = $(patsubst %.c, $(DEBUG_PATH_OBJS)%.o, $(SRCS))


#---------------------------------- THA RULES ---------------------------------#

all: $(PATH_OBJS) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(I_INCLUDES) $(OBJS) $(LIBFT) -o $@
	printf "$@ is ready.\n"

$(OBJS): $(PATH_OBJS)%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(I_INCLUDES) -c $< -o $@

$(PATH_OBJS):
	mkdir $@

$(LIBFT): FORCE 
	$(MAKE) -C $(PATH_LIB)

#---------------------------------- DEBUGGING ---------------------------------#


debug: $(DEBUG_PATH_OBJS) $(DEBUG_NAME)

$(DEBUG_NAME): $(LIBFT) $(DEBUG_OBJS)
	$(CC) $(DBFLAGS) $(I_INCLUDES) $(DEBUG_OBJS) $(LIBFT) -o $@
	printf "$@ is ready.\n"

$(DEBUG_OBJS): $(DEBUG_PATH_OBJS)%.o: %.c $(HEADER) Makefile
	$(CC) $(DBFLAGS) $(I_INCLUDES) -c $< -o $@

$(DEBUG_PATH_OBJS):
	mkdir $@

#---------------------------------- CLEANING ----------------------------------#

clean:
	$(RM) $(OBJS)
	$(RM) $(DEBUG_OBJS)
	$(RM) -R $(PATH_OBJS)
	$(RM) -R $(DEBUG_PATH_OBJS)
	$(RM) -R $(DSYM)
	$(MAKE) -C $(PATH_LIB) clean
	printf "Objs from $(NAME) removed\n"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(DEBUG_NAME)
	$(MAKE) -C $(PATH_LIB) fclean
	printf "$(NAME) removed\n"

re: fclean all

FORCE:

#------------------------------------- MISC -----------------------------------#

.PHONY: clean fclean re all
.SILENT:
