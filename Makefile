##
## Makefile for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/server/lib/libNetwork
##
## Made by Victorien LE COUVIOUR--TUFFET
## Login   <lecouv_v@epitech.eu>
##
## Started on  Wed Jun  8 18:46:12 2016 Victorien LE COUVIOUR--TUFFET
## Last update Mon Aug  1 17:38:07 2016 Victorien LE COUVIOUR--TUFFET
##

CC		= gcc

NAME		= $(BIN_PATH)libTCP.so

CFLAGS		+= -W -Wall -Werror -Wextra
CFLAGS		+= -I inc/
CFLAGS		+= -fPIC

LDFLAGS		= -shared -L lib/ -l tools

DIR_SRC		= src/

SRCS		= $(DIR_SRC)cl_rcv_msg.c	\
		  $(DIR_SRC)cl_read.c		\
		  $(DIR_SRC)cl_run.c		\
		  $(DIR_SRC)cl_snd_msg.c	\
		  $(DIR_SRC)cl_update.c		\
		  $(DIR_SRC)cl_write.c		\
		  $(DIR_SRC)srv_client_read.c	\
		  $(DIR_SRC)srv_client_write.c	\
		  $(DIR_SRC)srv_create_socket.c	\
		  $(DIR_SRC)srv_kick_client.c	\
		  $(DIR_SRC)srv_rcv_msg.c	\
		  $(DIR_SRC)srv_run.c		\
		  $(DIR_SRC)srv_server_read.c	\
		  $(DIR_SRC)srv_snd_msg.c	\
		  $(DIR_SRC)srv_update.c	\
		  $(DIR_SRC)tcp.c

OBJS		= $(SRCS:.c=.o)

RM		= rm -f
PRINTF		= @printf

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $@ $(LDFLAGS)
		$(PRINTF) '\033[1;32m> Compiled\033[0m\n'

clean:
		$(RM) $(OBJS)
		$(PRINTF) '\033[1;35m> Directory cleaned\033[0m\n'

fclean:		clean
		$(RM) $(NAME)
		$(PRINTF) '\033[1;35m> Remove binary\033[0m\n'

re:		fclean all

.PHONY:		all clean fclean re
