/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#include "struct_client.h"
#include "execute_request.h"
#include "prompt.h"
#include "client_error.h"
#include "sread.h"
#include "load_client_lexer.h"
#include "epure_str.h"
#include "auth_me_dude.h"

int		coffee_socket(char *ip, int port)
{
  int		sok;
  struct sockaddr_in addr;
  struct protoent *pe;

  pe = getprotobyname("TCP");
  if ((sok = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons(port);
  if (connect(sok, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    return (-1);
  return (sok);
}

void		run_client(struct_client *clt)
{
  int		r;
  t_cmd		*lexer;

  lexer = load_client_lexer();
  auth_me_dude(clt);
  while (clt->is_connected == TRUE)
    {
      prompt();
      bzero(clt->buffer, MAX_READ + 1);
      r = read(0, clt->buffer, MAX_READ);
      if (r == -1)
	client_error("read on standard input failed");
      else if (r > 0)
	{
	  clt->buffer[r] = '\0';
	  epure_str(clt->buffer);
	  execute_request(clt, lexer);
	}
    }
  prompt();
  printf("Disconnected.\n");
}

void            init_data_connection(struct_client *clt)
{
  char          ac[256];
  struct hostent *phe;
  struct in_addr locaddr;

  gethostname(ac, sizeof(ac));
  phe = gethostbyname(ac);
  memcpy(&locaddr, phe->h_addr_list[0], sizeof(struct in_addr));
  strcpy(clt->data.ip, inet_ntoa(locaddr));
  clt->data.sock = -1;
  clt->data.port = -1;
  clt->data.transfert_mode = PASV;
}

void		ftp_client(char *ip, int port)
{
  int		sock;
  struct_client	clt;

  if ((sock = coffee_socket(ip, port)) == -1)
    client_error("Could not connect to server");
  clt.sock = sock;
  if (sread(&clt) == -1)
    client_error("read on server socket failed");
  else
    printf("%s\n", clt.buffer);
  clt.is_connected = TRUE;
  init_data_connection(&clt);
  run_client(&clt);
  close(clt.sock);
}

