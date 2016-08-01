/*
** srv_client_read.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 18:54:29 2016 Victorien LE COUVIOUR--TUFFET
** Last update Thu Jul  7 17:27:28 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tcp_int.h"
#include "tools.h"

int		srv_client_read(t_srv_data *srv_data, t_srv_socket *socket)
{
  ssize_t	size;

  if ((size = read(socket->fd, socket->rd_buf + socket->rd_buf_idx,
		   BUF_SIZE - socket->rd_buf_idx)) <= 0)
    {
      if (size)
	print_error("Connection to client %s:%d lost.\n",
		    socket->ip, socket->port);
      else
	print_info("Connection to client %s:%d closed.\n",
		   socket->ip, socket->port);
      print_info("Server slots: %d / %d\n", --srv_data->connections_nb,
		 srv_data->slots_nb);
      if (close(socket->fd) == SYSERR)
	print_error_errno("unable to close client socket");
      socket->type = NONE;
      return (socket - srv_data->sockets - srv_data->ports_nb + 1);
    }
  else
    {
      socket->rd_buf_idx += size;
      print_info("Message of %ld bytes received from %s:%d\n\"%s\"\n",
		 socket->rd_buf_idx, socket->ip, socket->port, socket->rd_buf);
    }
  return (EXIT_SUCCESS);
}
