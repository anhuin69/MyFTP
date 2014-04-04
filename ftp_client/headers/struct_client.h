/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#ifndef		STRUCT_CLIENT_H_
# define	STRUCT_CLIENT_H_

# define	MAX_READ	2047
# define	PING_DELAY	300
# define	IP_MAX_SIZE	56

enum boolean
  {
    FALSE = 0,
    TRUE
  };

enum transfert_mode
  {
    PASV = 0,
    PORT
  };

typedef	struct	s_data
{
  int		sock;
  int		port;
  char		ip[IP_MAX_SIZE];
  int		transfert_mode;
}		t_data;

typedef	struct	s_struct_client
{
  int		sock;
  int		is_connected;
  t_data	data;
  char		buffer[MAX_READ + 1];
}		struct_client;

typedef	void (*cmd_ptr)(struct_client *clt);

typedef	struct	s_cmd
{
  char		*cmd;
  cmd_ptr	ptr;
  struct s_cmd	*next;
}		t_cmd;

#endif
