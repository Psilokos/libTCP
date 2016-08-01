/*
** srv_rcv_msg.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 18:54:02 2016 Victorien LE COUVIOUR--TUFFET
** Last update Thu Jul  7 17:35:50 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdlib.h>
#include <string.h>
#include "tcp_int.h"
#include "tools.h"
#include "tools_errors.h"

int	srv_rcv_msg(t_tcp_server *this, char **msg_ptr, size_t *size_ptr, int client_id)
{
  t_srv_data	*const srv_data = this->data;
  t_srv_socket	*const socket =
    srv_data->sockets + srv_data->ports_nb + --client_id;

  if (!socket->rd_buf_idx)
    {
      *msg_ptr = NULL;
      *size_ptr = 0;
    }
  else
    {
      if (!(*msg_ptr = malloc(socket->rd_buf_idx)))
	return (print_error("%s\n", ERR_OUTMEM));
      memcpy(*msg_ptr, socket->rd_buf, socket->rd_buf_idx);
      *size_ptr = socket->rd_buf_idx;
      memset(socket->rd_buf, 0, socket->rd_buf_idx);
      socket->rd_buf_idx = 0;
    }
  return (EXIT_SUCCESS);
}
