/*
** tcp.h for libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/server/lib/TCP
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Thu Jun  9 18:23:15 2016 Victorien LE COUVIOUR--TUFFET
** Last update Mon Aug  1 17:21:57 2016 Victorien LE COUVIOUR--TUFFET
*/

#ifndef TCP_H_
# define TCP_H_

# include <stdint.h>
# include <sys/types.h>

# define ERR_TCP	(-1)

typedef struct	s_tcp_client
{
  void		*data;
  int		(*run)(struct s_tcp_client *this, char *ip, uint16_t port);
  int		(*update)(struct s_tcp_client *this, struct timeval *timeout);
  int		(*rcv_msg)(struct s_tcp_client *this, char **msg_ptr, size_t *size_ptr);
  void		(*snd_msg)(struct s_tcp_client *this, char *msg, size_t size);
}		t_tcp_client;

typedef struct	s_tcp_server
{
  void		*data;
  int		(*run)(struct s_tcp_server *this, uint16_t ports[], size_t ports_nb, size_t slots_nb);
  int		(*update)(struct s_tcp_server *this, int new_clients_id[], int old_clients_id[], struct timeval *timeout);
  int		(*rcv_msg)(struct s_tcp_server *this, char **msg_ptr, size_t *size_ptr, int client_id);
  void		(*snd_msg)(struct s_tcp_server *this, char *msg, size_t size, int client_id);
  int		(*kick_client)(struct s_tcp_server *this, int client_id);
}		t_tcp_server;

t_tcp_client	*new_tcp_client(void);
t_tcp_server	*new_tcp_server(void);

void		delete_tcp_client(t_tcp_client *tcp_cl);
void		delete_tcp_server(t_tcp_server *tcp_srv);

#endif /* !TCP_H_ */
