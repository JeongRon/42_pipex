# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 21:32:47 by jeongrol          #+#    #+#              #
#    Updated: 2023/07/22 15:27:55 by jeongrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = bonus_pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

HEADER = mandatory/pipex.h
BONUS_HEADER = bonus/bonus_pipex.h

SRCS = 	mandatory/main.c \
		mandatory/util_libft.c \
		mandatory/util_pipex.c \
		mandatory/util_split.c \
		mandatory/set_info.c \
		mandatory/child.c \

BONUS_SRCS = bonus/bonus_main.c \
		bonus/bonus_util_libft.c \
		bonus/bonus_util_pipex.c \
		bonus/bonus_util_split.c \
		bonus/get_next_line_bonus.c \
		bonus/get_next_line_utils_bonus.c \
		bonus/bonus_set.c \
		bonus/bonus_exec.c \
		bonus/bonus_child.c \


OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

all:	$(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)
	
fclean:	clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re:
	make fclean
	make all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

bonus:	$(BONUS_NAME)

$(BONUS_NAME):	$(BONUS_OBJS) $(BONUS_HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS)

.PHONY:	all clean fclean re bonus