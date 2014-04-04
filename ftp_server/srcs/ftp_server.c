/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#include "struct_client.h"
#include "ftp_server.h"
#include "server_error.h"
#include "fork_client.h"
#include "load_lexer.h"

int		coffee_socket(int port)
{
  int		sok;
  struct sockaddr_in addr;
  struct protoent *pe;

  pe = getprotobyname("TCP");
  if ((sok = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    server_error(ERR_SCREATE);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  if (bind(sok, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    server_error(ERR_SBIND);
  if (listen(sok, MAX_NBR_CONNEC) == -1)
    server_error(ERR_SLISTEN);
  return (sok);
}

void		ftp_server(int port)
{
  int		serv_sock;
  int		new_sock;
  struct sockaddr_in adr;
  int		ads;
  int		pid;
  t_cmd		*cmd_lexer;

  ads = sizeof(adr);
  serv_sock = coffee_socket(port);
  cmd_lexer = load_lexer();
  printf("INFO : Server started on port %d.\n", port);
  while (1)
    {
      new_sock = accept(serv_sock, (struct sockaddr*)&adr, (socklen_t*)(&ads));
      if (new_sock > 0)
	{
	  if ((pid = fork()) == 0)
	    fork_client(new_sock, cmd_lexer, ads);
	  else if (pid > 0)
	    close(new_sock);
	  else
	    server_error("fork failed.");
	}
    }
  close(serv_sock);
}
