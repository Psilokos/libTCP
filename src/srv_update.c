/*
** srv_update.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 18:54:14 2016 Victorien LE COUVIOUR--TUFFET
** Last update Sat Jul  9 16:58:53 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include "tcp_int.h"
#include "tools.h"

static void	init_fds(t_srv_data *srv_data, fd_set *read_fds,
			 fd_set *write_fds, int *fd_max)
{
  size_t	i;

  FD_ZERO(read_fds);
  FD_ZERO(write_fds);
  *fd_max = 0;
  i = 0;
  while (i < srv_data->sockets_nb)
    {
      if (srv_data->sockets[i].type != NONE)
	{
	  FD_SET(srv_data->sockets[i].fd, read_fds);
	  if (srv_data->sockets[i].type == CLIENT)
	    FD_SET(srv_data->sockets[i].fd, write_fds);
	  if (srv_data->sockets[i].fd > *fd_max)
	    *fd_max = srv_data->sockets[i].fd;
	}
      ++i;
    }
}

static int	treat_read_fds(t_srv_data *srv_data, t_poop *poop,
			       int new_clients_id[], int old_clients_id[])
{
  int		ret;

  if (FD_ISSET(srv_data->sockets[poop->i].fd, &poop->read_fds))
    {
      if ((ret = srv_data->sockets[poop->i].fct_read
	   (srv_data, srv_data->sockets + poop->i)) == ERR_TCP)
	return (ret);
      else if (ret)
	{
	  if (srv_data->sockets[poop->i].type == SERVER)
	    new_clients_id[poop->j++] = ret;
	  else
	    old_clients_id[poop->k++] = ret;
	}
    }
  return (EXIT_SUCCESS);
}

static int		update_sockets(t_srv_data *const srv_data,
				       t_poop *poop,
				       int new_clients_id[],
				       int old_clients_id[])
{
  int			ret;

  poop->i = 0;
  poop->j = 0;
  poop->k = 0;
  while (poop->i < srv_data->sockets_nb)
    {
      if (treat_read_fds(srv_data, poop,
			 new_clients_id, old_clients_id) == ERR_TCP)
	return (ERR_TCP);
      if (srv_data->sockets[poop->i].type != NONE)
	{
	  if (srv_data->sockets[poop->i].type == CLIENT &&
	      FD_ISSET(srv_data->sockets[poop->i].fd, &poop->write_fds))
	    if ((ret = srv_data->sockets[poop->i].fct_write
		 (srv_data, srv_data->sockets + poop->i)))
	      old_clients_id[poop->k++] = ret;
	}
      ++poop->i;
    }
  return (EXIT_SUCCESS);
}

int			srv_update(t_tcp_server *this, int new_clients_id[],
				   int old_clients_id[],
				   struct timeval *timeout)
{
  t_srv_data		*const srv_data = this->data;
  int			fd_max;
  t_poop		poop;

  init_fds(srv_data, &poop.read_fds, &poop.write_fds, &fd_max);
  if (select(fd_max + 1, &poop.read_fds,
	     &poop.write_fds, NULL, timeout) == SYSERR)
    return (print_error_errno("t_tcp_server.update():"));
  memset(new_clients_id, 0, srv_data->slots_nb * sizeof(int));
  memset(old_clients_id, 0, srv_data->slots_nb * sizeof(int));
  return (update_sockets(srv_data, &poop, new_clients_id, old_clients_id));
}
