/*
** srv_kick_client.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Sun Jun 26 19:00:35 2016 Victorien LE COUVIOUR--TUFFET
** Last update Sun Jun 26 22:45:24 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tcp_int.h"
#include "tools.h"

int		srv_kick_client(t_tcp_server *this, int client_id)
{
  t_srv_data	*const srv_data = this->data;
  t_srv_socket	*const socket =
    srv_data->sockets + srv_data->ports_nb + --client_id;

  if (close(socket->fd) == SYSERR)
    return (print_error_errno("unable to kick client %d", client_id));
  print_info("Client %s:%p has been kicked.\n",
	     socket->ip, socket->port);
  print_info("Server slots: %d / %d\n", --srv_data->connections_nb,
	     srv_data->slots_nb);
  memset(socket, 0, sizeof(t_srv_socket));
  return (EXIT_SUCCESS);
}
