# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/23 21:06:44 by ablanco-          #+#    #+#              #
#    Updated: 2024/03/16 13:17:54 by ablanco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC = main.c time.c utils.c parse.c init.c end.c rutine.c 

OBJS = ${SRC:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -o3 -pthread #-g3 -fsanitize=thread


RM = rm -rf

all: ${NAME}

${NAME}:	${OBJS}
			$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

exe:
	./$(NAME)

clean:
		@${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean exe fclean re all
