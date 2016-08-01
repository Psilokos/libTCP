/*
** srv_server_read.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 18:54:09 2016 Victorien LE COUVIOUR--TUFFET
** Last update Fri Jul  8 13:43:12 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "tcp_int.h"
#include "tools.h"

static int		accept_new_client(t_srv_socket sockets[], int s_sockfd)
{
  struct sockaddr_in	cl_sockaddr;
  socklen_t		cl_sockaddr_size;
  int			cl_sockfd;
  bool const		is_connected = true;

  cl_sockaddr_size = sizeof(cl_sockaddr);
  if ((cl_sockfd = accept(s_sockfd, (struct sockaddr *)&cl_sockaddr,
			  &cl_sockaddr_size)) == SYSERR)
    return (-print_error_errno("accept"));
  if (!sockets)
    {
      if (close(cl_sockfd) == SYSERR)
	return (print_error_errno("close"));
      return (EXIT_SUCCESS);
    }
  write(cl_sockfd, &is_connected, sizeof(bool));
  return (srv_init_socket(sockets, CLIENT, cl_sockfd, &cl_sockaddr));
}

int	srv_server_read(t_srv_data *srv_data, t_srv_socket *socket)
{
  int	socket_id;

  print_info("Accepting new client... ");
  if (srv_data->connections_nb == srv_data->slots_nb)
    {
      print_warning("Server is full\n");
      return (accept_new_client(NULL, socket->fd));
    }
  if ((socket_id = accept_new_client(srv_data->sockets, socket->fd)) == -1)
    return (EXIT_FAILURE);
  print_info("OK\n");
  print_info("New client connected.\n");
  print_info("Server slots: %d / %d\n",
	     ++srv_data->connections_nb, srv_data->slots_nb);
  return (socket_id - srv_data->ports_nb + 1);
}
