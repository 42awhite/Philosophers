

NAME = philo;

SRC = main.c, time.c

OBJ = ${SRC:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: {NAME}

