# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 21:32:47 by jeongrol          #+#    #+#              #
#    Updated: 2023/06/20 21:41:45 by jeongrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

HEADER = mandatory/pipex.h
# BONUS_HEADER = 

SRCS = 	mandatory/main.c \
		mandatory/util_libft.c \
		mandatory/util_pipex.c \
		mandatory/util_split.c \
		mandatory/set_info.c \
		mandatory/child.c \

# B_SRCS = 

OBJS = ${SRCS:.c=.o}
# B_OBJS = ${B_SRCS:.c=.o}

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

# bonus:	$(BONUS_NAME)

# $(BONUS_NAME):	$(BONUS_OBJS) $(BONUS_HEADER)
	# $(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS)

.PHONY:	all clean fclean re bonus