/*
** cl_main.c for test_libTCP in /home/lecouv_v/rendu/PSU_2015_zappy/lib
**
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.eu>
**
** Started on  Fri Jun 24 17:05:11 2016 Victorien LE COUVIOUR--TUFFET
** Last update Mon Aug  1 18:14:24 2016 Victorien LE COUVIOUR--TUFFET
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include "tcp.h"
#include "tools.h"

int			main(int argc, char *argv[])
{
  t_tcp_client		*cl;
  char			*msg = NULL;
  char			buf[8192] = {0};
  int			ret = EXIT_SUCCESS;
  int			read_ret;
  fd_set		read_fds;
  struct timeval	timeout = {.tv_sec = 0, .tv_usec = 0};
  int			pseudo_len;

  if (argc < 4)
    return (print_err("usage", "<username> <server ip> <server port>"));
  strcpy(buf, argv[1]);
  strcat(buf, ": ");
  pseudo_len = strlen(buf);
  init_tools(*argv);
  if (!(cl = new_tcp_client()))
    return (EXIT_FAILURE);
  if (cl->run(cl, argv[2], atoi(argv[3])))
    return (EXIT_FAILURE);
  while (1)
    {
      size_t	size;

      FD_ZERO(&read_fds);
      FD_SET(0, &read_fds);
      if (select(1, &read_fds, NULL, NULL, (struct timeval *)&timeout) == SYSERR)
	{
	  ret = EXIT_FAILURE;
	  break ;
	}
      if (FD_ISSET(0, &read_fds))
	{
	  if ((read_ret = read(STDIN_FILENO, buf + pseudo_len, 8191 - pseudo_len)) == SYSERR)
	    {
	      ret = EXIT_FAILURE;
	      break ;
	    }
	  if (!read_ret)
	    {
	      ret = EXIT_SUCCESS;
	      break ;
	    }
	  buf[pseudo_len + read_ret] = 0;
	  if (*buf)
	    {
	      cl->snd_msg(cl, buf, strlen(buf) + 1);
	      memset(buf + pseudo_len, 0, 8192 - pseudo_len);
	    }
	  printf("%s: ", argv[1]);
	  fflush(stdout);
	}
      if (cl->update(cl, &timeout) || cl->rcv_msg(cl, &msg, &size))
	{
	  ret = EXIT_FAILURE;
	  break ;
	}
      if (msg)
	{
	  puts("");
	  write(STDOUT_FILENO, msg, size);
	  printf("%s: ", argv[1]);
	  fflush(stdout);
	  free(msg);
	}
    }
  delete_tcp_client(cl);
  destroy_tools();
  return (ret);
}
