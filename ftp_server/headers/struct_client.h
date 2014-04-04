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

#include <sys/time.h>
#include <sys/types.h>

# define	SERV_ROOT_DIR	"server_root_dir"

# define	MAX_READ	2047
# define	PATH_MAX_LENGHT	2048
# define	IP_MAX_SIZE	56
# define	PING_DELAY	300

# define	ERR_SELECT	"Select error"
# define	ERR_READ	"Read error"
# define	ERR_WRITE	"Write error"
# define	ERR_TIMEOUT	"Connection timed out"
# define	ERR_CONTEXT	"Impossible to create client context"
# define	CLIENT_QUIT	"Client disconnected"

enum boolean
  {
    FALSE = 0,
    TRUE
  };

enum log_status
  {
    NOT_LOG = 0,
    LOGGED,
    AUTH
  };

enum transfert_mode
  {
    UNSET = 0,
    PASV,
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
  t_data	data;
  int		is_connected;
  struct timeval tm;
  fd_set	fs;
  char		buffer[MAX_READ + 1];
  int		is_logged;
  char		root_path[PATH_MAX_LENGHT];
  char		*file_to_rename;
  const char	*error;
}		struct_client;

typedef	void (*cmd_ptr)(struct_client *clt);

typedef	struct	s_cmd
{
  char		*cmd;
  cmd_ptr	ptr;
  struct s_cmd	*next;
}		t_cmd;

#endif
