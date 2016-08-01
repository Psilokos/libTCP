/*
** srv_main.c for test_libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Fri Jun 24 17:05:20 2016 Victorien LE COUVIOUR--TUFFET
** Last update Mon Aug  1 18:19:35 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tcp.h"
#include "tools.h"

#define SRV_SIZE	(16)

typedef struct	s_client
{
  int		id;
  char		*msg;
}		t_client;

t_tcp_server	*srv;

static void	sighandler(int signum)
{
  if (signum == SIGINT)
    {
      delete_tcp_server(srv);
      destroy_tools();
      exit(EXIT_SUCCESS);
    }
}

int			main(__attribute__ (( unused )) int argc, char *argv[])
{
  uint16_t		ports[3] = {4242, 2121, 444};
  int			ret;
  t_client		clients[SRV_SIZE];
  int			clients_nb = 0;
  int			i;
  int			j;
  int			new_clients_id[SRV_SIZE];
  int			old_clients_id[SRV_SIZE];
  struct timeval	timeout = {.tv_sec = 0, .tv_usec = 0};

  if (signal(SIGINT, &sighandler) == SIG_ERR)
    return (EXIT_FAILURE);
  init_tools(*argv);
  if (!(srv = new_tcp_server()))
    return (EXIT_FAILURE);
  if (srv->run(srv, ports, 3, SRV_SIZE))
    return (EXIT_FAILURE);
  while (1)
    {
      for (i = 0; i < clients_nb; ++i)
	if (clients[i].msg)
	  {
	    for (j = 0; j < clients_nb; ++j)
	      if (j != i)
		srv->snd_msg(srv, clients[i].msg, strlen(clients[i].msg) + 1, clients[j].id);
	    free(clients[i].msg);
	    clients[i].msg = NULL;
	  }
      if ((ret = srv->update(srv, new_clients_id, old_clients_id, &timeout)) == ERR_TCP)
	return (EXIT_FAILURE);
      i = 0;
      while (new_clients_id[i])
	{
	  clients[clients_nb].id = new_clients_id[i++];
	  clients[clients_nb++].msg = NULL;
	}
      i = 0;
      while (old_clients_id[i])
	printf("Client %d disconnected\n", old_clients_id[i++]);
      i = 0;
      while (i < clients_nb)
	{
	  size_t	size;

	  srv->rcv_msg(srv, &clients[i].msg, &size, clients[i].id);
	  if (clients[i].msg && strstr(clients[i].msg, "/kill_server"))
	    goto end;
	  else if (clients[i].msg && strstr(clients[i].msg, "/kick_me"))
	    srv->kick_client(srv, clients[i].id);
	  ++i;
	}
    }
 end:
  i = 0;
  while (i < clients_nb)
    {
      if (clients[i].msg)
	free(clients[i].msg);
      ++i;
    }
  delete_tcp_server(srv);
  destroy_tools();
  return (EXIT_SUCCESS);
}
