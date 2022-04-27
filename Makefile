# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 01:49:00 by fcavillo          #+#    #+#              #
#    Updated: 2022/04/27 17:20:00 by fcavillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC	= clang++

CFLAGS	= -Wall -Wextra -Werror -std=c++98

SRCS =	main.cpp \
		srcs/classes/Server.cpp \
		srcs/classes/Channel.cpp \
		srcs/classes/Client.cpp \
		srcs/classes/Message.cpp \
		srcs/classes/cmds/cmds_parsing.cpp \
		srcs/classes/cmds/cmds_pass.cpp \

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

${NAME}: $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all : ${NAME}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY:	all clean re fclean re
