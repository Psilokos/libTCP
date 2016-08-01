/*
** srv_run.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 18:54:21 2016 Victorien LE COUVIOUR--TUFFET
** Last update Fri Jun 24 23:00:55 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "tcp_int.h"
#include "tools.h"

static int	open_ports(t_srv_data *srv_data, uint16_t ports[], size_t ports_nb)
{
  size_t	i;
  int		success_nb;

  i = 0;
  success_nb = 0;
  while (i < ports_nb)
    {
      print_info("Initializing socket on port: %d... ", ports[i]);
      if (srv_create_socket(srv_data->sockets, ports[i],
			    srv_data->slots_nb, SERVER))
	{
	  --srv_data->ports_nb;
	  print_warning("%d port(s) remaining\n", ports_nb - (i + 1));
	}
      else
	++success_nb;
      ++i;
    }
  if (success_nb)
    print_info("%d / %d socket(s) %s operationnal.\n", success_nb, ports_nb,
	       ((success_nb == 1) ? ("is") : ("are")));
  else
    return (print_error("No socket has been created, \
given ports might be unavailable\n"));
  return (EXIT_SUCCESS);
}

static int		init_server(t_srv_data *srv_data, uint16_t ports[],
				    size_t ports_nb, size_t slots_nb)
{
  srv_data->sockets_nb = ports_nb + slots_nb;
  srv_data->ports_nb = ports_nb;
  srv_data->slots_nb = slots_nb;
  srv_data->connections_nb = 0;
  if (!(srv_data->sockets = malloc(srv_data->sockets_nb * sizeof(t_srv_socket))))
    return (print_err("t_tcp_server.run()", strerror(ENOMEM)));
  memset(srv_data->sockets, 0, srv_data->sockets_nb * sizeof(t_srv_socket));
  return (open_ports(srv_data, ports, ports_nb));
}

int		srv_run(t_tcp_server *this, uint16_t ports[],
			size_t ports_nb, size_t slots_nb)
{
  size_t	i;

  if (!ports || !ports[0])
    return (print_error("t_tcp_server.run(): \
you must specifie at least one port"));
  print_info("Running server on ports %d", ports[0]);
  i = 1;
  while (i < ports_nb)
    print_info(", %d", ports[i++]);
  print_info("...\n");
  if (init_server(this->data, ports, ports_nb, slots_nb))
    return (EXIT_FAILURE);
  print_info("Server launched successfully\n");
  return (EXIT_SUCCESS);
}
