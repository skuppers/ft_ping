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

.SUFFIXES:

NAME=ft_ping

CC=clang

PATH_LIB=libft/

LIBFT= $(PATH_LIB)libft.a

CFLAGS += -Wall
CFLAGS += -Wextra

# Compiler Debug Flags
ifeq ($(d), 0)
	CFLAGS += -g3
else ifeq ($(d), 1)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
else ifeq ($(d), 2)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
else ifeq ($(d), 3)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
	CFLAGS += -pedantic
else ifeq ($(d), 4)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
	CFLAGS += -pedantic
	CFLAGS += -Weverything
endif
ifneq ($(err), no)
	CFLAGS += -Werror
endif

# Debug Dir
DSYM += $(NAME).dSYM
DSYM += $(DBNAME).dSYM

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
SRCS += validate_options.c

vpath %.c $(PATH_SRCS)

#----------------------------------- OBJECTS ----------------------------------#

PATH_OBJS = objs/
OBJS = $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

DEBUG_PATH_OBJS = objs_debug/
DEBUG_OBJS = $(patsubst %.c, $(DEBUG_PATH_OBJS)%.o, $(SRCS))


#-----------------------------------  RULES  -----------------------------------#

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


#---------------------------------- CLEANING ----------------------------------#

clean:
	$(RM) $(OBJS)
	$(RM) $(DEBUG_OBJS)
	$(RM) -R $(PATH_OBJS)
	$(RM) -R $(DSYM)
	$(MAKE) -C $(PATH_LIB) clean
	printf "Objs from $(NAME) removed\n"

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(PATH_LIB) fclean
	printf "$(NAME) removed\n"

re: fclean all

FORCE:

#------------------------------------- MISC -----------------------------------#

.PHONY: clean fclean re all
.SILENT:
