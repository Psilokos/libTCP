/*
** tools.h for tools in /home/lecouv_v/rendu/PSU_2015_myftp
** 
** Made by Victorien LE COUVIOUR--TUFFET
** Login   <lecouv_v@epitech.net>
** 
** Started on  Sat May 14 18:20:18 2016 Victorien LE COUVIOUR--TUFFET
** Last update Thu May 19 01:55:03 2016 Victorien LE COUVIOUR--TUFFET
*/

#ifndef TOOLS_H_
# define TOOLS_H_

# define SWAP(a, b)	(a ^= (b = (a ^= b) ^ b))

# define SYSERR		(-1)

enum e_logtype
  {
    INFO,
    WARNING,
    ERROR
  };

/*
** init and destroy functions
*/
int	init_tools(char *bin_name);
int	destroy_tools(void);

/*
** argument retrieve
*/
char	*get_arg(char *argv[], char *arg);
int	get_arg_pos(char *argv[], char *arg);
char	**get_arg_addr(char *argv[], char *arg);

/*
** error printing
*/
int	print_err(char *context, char *msg);
int	print_errno(char *msg);

/*
** log
*/
void	print_info(char *fmt, ...);
void	print_warning(char *fmt, ...);
int	print_error(char *fmt, ...);
int	print_error_errno(char *fmt, ...);

#endif /* !TOOLS_H_ */
