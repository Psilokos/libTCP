/*
** cl_rcv_msg.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 19:56:04 2016 Victorien LE COUVIOUR--TUFFET
** Last update Fri Jul  8 13:44:00 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdlib.h>
#include <string.h>
#include "tcp_int.h"
#include "tools.h"
#include "tools_errors.h"

int		cl_rcv_msg(t_tcp_client *this,
			   char **msg_ptr, size_t *size_ptr)
{
  t_cl_socket	*const socket = this->data;

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
      socket->rd_buf[(socket->rd_buf_idx = 0)] = 0;
    }
  return (EXIT_SUCCESS);
}
