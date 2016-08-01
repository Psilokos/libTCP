/*
** tcp_int.h for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/server/lib/TCP
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun  9 19:08:36 2016 Victorien LE COUVIOUR--TUFFET
** Last update Sat Jul  9 17:01:12 2016 Victorien LE COUVIOUR--TUFFET
*/

#ifndef TCP_INT_H_
# define TCP_INT_H_

# include <netinet/in.h>
# include <stdbool.h>
# include <sys/types.h>
# include "tcp.h"

# define BUF_SIZE	(8192)

typedef enum	s_socktype
  {
    NONE,
    CLIENT,
    SERVER
  }		t_socktype;

typedef int	(*fct_ptr)();

typedef struct	s_cl_socket
{
  int		fd;
  char		ip[16];
  uint16_t	port;
  char		rd_buf[BUF_SIZE];
  char		wr_buf[BUF_SIZE];
  int		rd_buf_idx;
  int		wr_buf_idx;
}		t_cl_socket;

typedef struct	s_srv_socket
{
  t_socktype	type;
  int		fd;
  char		ip[16];
  uint16_t	port;
  char		rd_buf[BUF_SIZE];
  char		wr_buf[BUF_SIZE];
  int		rd_buf_idx;
  int		wr_buf_idx;
  fct_ptr	fct_read;
  fct_ptr	fct_write;
}		t_srv_socket;

typedef struct	s_srv_data
{
  t_srv_socket	*sockets;
  size_t	sockets_nb;
  size_t	ports_nb;
  size_t	slots_nb;
  size_t	connections_nb;
}		t_srv_data;

typedef struct	s_poop
{
  fd_set	read_fds;
  fd_set	write_fds;
  size_t	i;
  int		j;
  int		k;
}		t_poop;

/*
** public methods
*/

int	cl_run(t_tcp_client *this, char *ip, uint16_t port);
int	cl_update(t_tcp_client *this, struct timeval *timeout);
int	cl_rcv_msg(t_tcp_client *this, char **msg_ptr, size_t *size_ptr);
void	cl_snd_msg(t_tcp_client *this, char *msg, size_t size);

int	srv_run(t_tcp_server *this, uint16_t ports[],
		size_t ports_nb, size_t slots_nb);
int	srv_update(t_tcp_server *this, int new_clients_id[],
		   int old_clients_id[], struct timeval *timeout);
int	srv_rcv_msg(t_tcp_server *this, char **msg_ptr, size_t *size_ptr, int client_id);
void	srv_snd_msg(t_tcp_server *this, char *msg, size_t size, int client_id);
int	srv_kick_client(t_tcp_server *this, int client_id);

/*
** private methods
*/

int	cl_read(t_cl_socket *socket);
int	cl_write(t_cl_socket *socket);

int	srv_create_socket(t_srv_socket sockets[], uint16_t port,
			  uint32_t max_connections_nb,
			  t_socktype socktype);
int	srv_init_socket(t_srv_socket sockets[], t_socktype socktype,
			int sockfd, struct sockaddr_in *sockaddr);
int	srv_server_read(t_srv_data *srv_data, t_srv_socket *socket);
int	srv_client_read(t_srv_data *srv_data, t_srv_socket *socket);
int	srv_client_write(t_srv_data *srv_data, t_srv_socket *socket);

#endif /* !TCP_INT_H_ */
