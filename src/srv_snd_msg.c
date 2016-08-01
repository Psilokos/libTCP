/*
** srv_snd_msg.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 18:54:18 2016 Victorien LE COUVIOUR--TUFFET
** Last update Thu Jul  7 17:30:28 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <string.h>
#include "tcp_int.h"

void	srv_snd_msg(t_tcp_server *this, char *msg, size_t size, int client_id)
{
  t_srv_data	*const srv_data = this->data;
  t_srv_socket	*const socket =
    srv_data->sockets + srv_data->ports_nb + --client_id;
  int const	len = (((ssize_t)size < BUF_SIZE - socket->wr_buf_idx)
		       ? ((ssize_t)size)
		       : (BUF_SIZE - socket->wr_buf_idx));

  strncat(socket->wr_buf, msg, len);
  socket->wr_buf_idx += len;
}
