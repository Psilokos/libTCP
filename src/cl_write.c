/*
** cl_write.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 19:09:44 2016 Victorien LE COUVIOUR--TUFFET
** Last update Sun Jul 10 12:59:17 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tcp_int.h"
#include "tools.h"

static ssize_t	send_msg_to_server(t_cl_socket *socket)
{
  ssize_t	size;

  if ((size = send(socket->fd, socket->wr_buf, socket->wr_buf_idx, 0)) <= 0)
    {
      if (size)
	return (print_error_errno("Connection to server %s:%d lost",
				  socket->ip, socket->port));
      else
	return (print_error("Connection to server %s:%d lost.",
			    socket->ip, socket->port));
    }
  return (size);
}

int		cl_write(t_cl_socket *socket)
{
  ssize_t	size;

  if (socket->wr_buf_idx)
    {
      if ((size = send_msg_to_server(socket)) > 0)
	{
	  if (size < socket->wr_buf_idx)
	    {
	      memmove(socket->wr_buf, socket->wr_buf + size,
		      socket->wr_buf_idx - size);
	      socket->wr_buf_idx -= size;
	    }
	  else
	    socket->wr_buf[(socket->wr_buf_idx = 0)] = 0;
	}
      else
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
