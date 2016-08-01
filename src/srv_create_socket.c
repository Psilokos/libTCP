/*
** srv_create_socket.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP/src
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 18:54:25 2016 Victorien LE COUVIOUR--TUFFET
** Last update Fri Jun 24 17:00:27 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "tcp_int.h"
#include "tools.h"

int		srv_init_socket(t_srv_socket sockets[], t_socktype socktype,
				int sockfd, struct sockaddr_in *sockaddr)
{
  size_t	i;

  i = 0;
  while (sockets[i].type != NONE)
    ++i;
  sockets[i].type = socktype;
  sockets[i].fd = sockfd;
  strcpy(sockets[i].ip, inet_ntoa(sockaddr->sin_addr));
  sockets[i].port = ntohs(sockaddr->sin_port);
  if (socktype == CLIENT)
    {
      sockets[i].fct_read = &srv_client_read;
      sockets[i].fct_write = &srv_client_write;
    }
  else
    sockets[i].fct_read = &srv_server_read;
  return (i);
}

int				srv_create_socket(t_srv_socket sockets[],
						  uint16_t port,
						  uint32_t max_connection_nb,
						  t_socktype socktype)
{
  static struct protoent	*pe;
  struct sockaddr_in		sockaddr;
  int				sockfd;

  if (socktype != CLIENT && socktype != SERVER)
    return (print_error("given socket type is unknown"));
  if (!pe)
    if (!(pe = getprotobyname("TCP")))
      return (print_error("cannot retrieve protocol info"));
  if ((sockfd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == SYSERR)
    return (print_error_errno("new socket opening failed"));
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_port = htons(port);
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd, (struct sockaddr const *)&sockaddr,
	   sizeof(struct sockaddr_in)) == SYSERR)
    return (print_error_errno("new socket binding failed"));
  if (listen(sockfd, max_connection_nb) == SYSERR)
    return (print_error_errno("new socket listening failed"));
  srv_init_socket(sockets, socktype, sockfd, &sockaddr);
  print_info("OK\n");
  return (EXIT_SUCCESS);
}
