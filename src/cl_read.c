/*
** cl_read.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 19:03:43 2016 Victorien LE COUVIOUR--TUFFET
** Last update Sun Jul 10 12:59:05 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdlib.h>
#include <unistd.h>
#include "tcp_int.h"
#include "tools.h"

int		cl_read(t_cl_socket *socket)
{
  ssize_t	size;

  if ((size = recv(socket->fd, socket->rd_buf + socket->rd_buf_idx,
		   BUF_SIZE - socket->rd_buf_idx, 0)) <= 0)
    {
      if (size)
	return print_error_errno("Connection to server %s:%d lost\n",
				 socket->ip, socket->port);
      else
	return (print_error("Connection to server %s:%d lost.\n",
			    socket->ip, socket->port));
    }
  else
    socket->rd_buf_idx += size;
  return (EXIT_SUCCESS);
}
