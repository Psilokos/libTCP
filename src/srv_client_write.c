/*
** srv_client_write.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 18:53:56 2016 Victorien LE COUVIOUR--TUFFET
** Last update Sun Jun 26 20:52:09 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tcp_int.h"
#include "tools.h"

static ssize_t	send_msg_to_client(t_srv_data *srv_data, t_srv_socket *socket)
{
  ssize_t	size;

  if ((size = write(socket->fd, socket->wr_buf, socket->wr_buf_idx)) <= 0)
    {
      if (size)
	print_error("Connection to client %s:%d lost.\n",
		    socket->ip, socket->port);
      else
	print_info("Connection to client %s:%d closed.\n",
		   socket->ip, socket->port);
      print_info("Server slots: %d / %d\n",
		 --srv_data->connections_nb, srv_data->slots_nb);
      if (close(socket->fd) == SYSERR)
	print_error_errno("unable to close client socket");
      socket->type = NONE;
      return (-(socket - srv_data->sockets - srv_data->ports_nb + 1));
    }
  return (size);
}

int		srv_client_write(t_srv_data *srv_data, t_srv_socket *socket)
{
  ssize_t	size;

  if (socket->wr_buf_idx)
    {
      if ((size = send_msg_to_client(srv_data, socket)) > 0)
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
	return (-size);
    }
  return (EXIT_SUCCESS);
}
