##
## Makefile for test_libTCP in /home/lecouv_v/rendu/libTCP/test_libTCP
##
## Made by Victorien LE COUVIOUR--TUFFET
## Login   <lecouv_v@epitech.eu>
##
## Started on  Mon Aug  1 17:39:57 2016 Victorien LE COUVIOUR--TUFFET
## Last update Mon Aug  1 17:54:35 2016 Victorien LE COUVIOUR--TUFFET
##

CC		= gcc

NAME_CLIENT	= cl
NAME_SERVER	= srv

CFLAGS		+= -W -Wall -Werror -Wextra
CFLAGS		+= -I ../inc/

LDFLAGS		= -L ./ -l TCP -l tools -Wl,-rpath='$$ORIGIN/./'

DIR_SRC		=

SRCS_CLIENT	= $(DIR_SRC)cl_main.c
SRCS_SERVER	= $(DIR_SRC)srv_main.c

OBJS_CLIENT	= $(SRCS_CLIENT:.c=.o)
OBJS_SERVER	= $(SRCS_SERVER:.c=.o)

RM		= rm -f
PRINTF		= @printf

all:		$(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT):	$(OBJS_CLIENT)
		$(CC) $(OBJS_CLIENT) -o $@ $(LDFLAGS)
		$(PRINTF) '\033[1;32m> Client compiled\033[0m\n'

$(NAME_SERVER):	$(OBJS_SERVER)
		$(CC) $(OBJS_SERVER) -o $@ $(LDFLAGS)
		$(PRINTF) '\033[1;32m> Server compiled\033[0m\n'

clean:
		$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)
		$(PRINTF) '\033[1;35m> Directory cleaned\033[0m\n'

fclean:		clean
		$(RM) $(NAME_CLIENT) $(NAME_SERVER)
		$(PRINTF) '\033[1;35m> Binaries removed\033[0m\n'

re:		fclean all

.PHONY:		all clean fclean re
