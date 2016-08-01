/*
** tcp_cl_run.c for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib/TCP
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun 23 17:18:14 2016 Victorien LE COUVIOUR--TUFFET
** Last update Thu Jul  7 18:21:26 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "tcp_int.h"
#include "tools.h"

static int	init_client(t_cl_socket *cl_socket, char *ip, uint16_t port)
{
  struct protoent	*pe;
  struct sockaddr_in	sockaddr;
  int			sockfd;

  print_info("Initializing socket on port: %d\n", port);
  memset(cl_socket, 0, sizeof(t_cl_socket));
  if (!(pe = getprotobyname("TCP")))
    return (print_error("cannot retrieve protocol info"));
  if ((sockfd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == SYSERR)
    return (print_error_errno("socket opening failed"));
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_port = htons(port);
  sockaddr.sin_addr.s_addr = inet_addr(ip);
  if (connect(sockfd, (struct sockaddr const *)&sockaddr,
	      sizeof(struct sockaddr_in)) == SYSERR)
    return (print_error_errno("socket connection failed"));
  cl_socket->fd = sockfd;
  strcpy(cl_socket->ip, ip);
  cl_socket->port = port;
  return (EXIT_SUCCESS);
}

int		cl_run(t_tcp_client *this, char *ip, uint16_t port)
{
  if (!ip || strlen(ip) < 7)
    return (print_error("t_tcp_server.run(): \
you must specifie a valid ip"));
  print_info("Runnning client on port %d\n", port);
  if (init_client(this->data, ip, port))
    return (print_error("socket connection failed"));
  print_info("Client launched successfully\n");
  return (EXIT_SUCCESS);
}
