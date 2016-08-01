/*
** cl_update.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 18:55:48 2016 Victorien LE COUVIOUR--TUFFET
** Last update Sat Jul  9 16:55:54 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdlib.h>
#include <sys/select.h>
#include "tcp_int.h"
#include "tools.h"

int			cl_update(t_tcp_client *this, struct timeval *timeout)
{
  t_cl_socket	*const	cl_socket = this->data;
  fd_set		read_fds;
  fd_set		write_fds;

  FD_ZERO(&read_fds);
  FD_ZERO(&write_fds);
  FD_SET(cl_socket->fd, &read_fds);
  FD_SET(cl_socket->fd, &write_fds);
  if (select(cl_socket->fd + 1, &read_fds,
	     &write_fds, NULL, timeout) == SYSERR)
    return (print_error_errno("t_tcp_client.update():"));
  if (FD_ISSET(cl_socket->fd, &read_fds))
    if (cl_read(cl_socket))
      return (EXIT_FAILURE);
  if (FD_ISSET(cl_socket->fd, &write_fds))
    if (cl_write(cl_socket))
      return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
