/*
** tcp.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/server/lib/TCP
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun  9 18:32:28 2016 Victorien LE COUVIOUR--TUFFET
** Last update Sun Jun 26 19:06:10 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tcp_int.h"
#include "tools.h"

t_tcp_client	*new_tcp_client(void)
{
  t_tcp_client	*tcp_cl;

  if (!(tcp_cl = malloc(sizeof(t_tcp_client) + sizeof(t_cl_socket))))
    {
      print_err("new_tcp_client", strerror(ENOMEM));
      return (NULL);
    }
  tcp_cl->data = (void *)tcp_cl + sizeof(t_tcp_client);
  tcp_cl->run = &cl_run;
  tcp_cl->update = &cl_update;
  tcp_cl->rcv_msg = &cl_rcv_msg;
  tcp_cl->snd_msg = &cl_snd_msg;
  return (tcp_cl);
}

t_tcp_server	*new_tcp_server(void)
{
  t_tcp_server	*tcp_srv;

  if (!(tcp_srv = malloc(sizeof(t_tcp_server) + sizeof(t_srv_data))))
    {
      print_err("new_tcp_server", strerror(ENOMEM));
      return (NULL);
    }
  tcp_srv->data = (void *)tcp_srv + sizeof(t_tcp_server);
  tcp_srv->run = &srv_run;
  tcp_srv->update = &srv_update;
  tcp_srv->rcv_msg = &srv_rcv_msg;
  tcp_srv->snd_msg = &srv_snd_msg;
  tcp_srv->kick_client = &srv_kick_client;
  return (tcp_srv);
}

void		delete_tcp_client(t_tcp_client *tcp_cl)
{
  t_cl_socket	*const cl_socket = tcp_cl->data;

  if (close(cl_socket->fd) == SYSERR)
    print_error_errno("unable to close fd %d\n", cl_socket->fd);
  free(tcp_cl);
}

void		delete_tcp_server(t_tcp_server *tcp_srv)
{
  t_srv_data	*const srv_data = tcp_srv->data;
  size_t	i;

  i = 0;
  while (i < srv_data->sockets_nb)
    {
      if (srv_data->sockets[i].type)
	if (close(srv_data->sockets[i].fd) == SYSERR)
	  print_error_errno("unable to close socket fd %d\n", srv_data->sockets[i].fd);
      ++i;
    }
  free(srv_data->sockets);
  free(tcp_srv);
}
