/*
** cl_snd_msg.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 19:59:45 2016 Victorien LE COUVIOUR--TUFFET
** Last update Fri Jul  8 13:43:27 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <string.h>
#include "tcp_int.h"

void		cl_snd_msg(t_tcp_client *this, char *msg, size_t size)
{
  t_cl_socket	*const socket = this->data;
  int const	len = (((ssize_t)size < BUF_SIZE - socket->wr_buf_idx)
		       ? ((ssize_t)size)
		       : (BUF_SIZE - socket->wr_buf_idx));

  strncat(socket->wr_buf, msg, len);
  socket->wr_buf_idx += len;
}
