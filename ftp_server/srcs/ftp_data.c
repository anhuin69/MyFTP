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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "struct_client.h"

int		new_data_chan(t_data *data)
{
  struct sockaddr_in addr;
  socklen_t	alen;
  struct protoent *pe;

  pe = getprotobyname("TCP");
  if ((data->sock = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = 0;
  if (bind(data->sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    return (-1);
  if (listen(data->sock, 1) == -1)
    return (-1);
  alen = sizeof(addr);
  if (getsockname(data->sock, (struct sockaddr*)&addr, &alen) == -1)
    return (-1);
  data->port = ntohs(addr.sin_port);
  return (0);
}

void		close_data_chan(struct_client *clt, int nsock)
{
  close(clt->data.sock);
  if (nsock > 0)
    close(nsock);
  clt->data.port = -1;
  clt->data.transfert_mode = UNSET;
}

int		accept_data_client(struct_client *clt)
{
  struct sockaddr_in ar;
  int		a;
  int		nsock;

  a = sizeof(ar);
  nsock = accept(clt->data.sock, (struct sockaddr*)&ar, (socklen_t*)(&a));
  if (nsock < 0)
    {
      close_data_chan(clt, nsock);
      fprintf(stderr, "Error accept\n");
      return (-1);
    }
  return (nsock);
}

int		connect_to_client(struct_client *clt)
{
  int		sok;
  int		on;
  struct sockaddr_in addr;
  struct protoent *pe;

  pe = getprotobyname("TCP");
  if ((sok = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  on = setsockopt(sok, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));
  if (on == -1)
    return (on);
  addr.sin_family = AF_INET;
  inet_pton(AF_INET, clt->data.ip, &(addr.sin_addr));
  addr.sin_port = htons(clt->data.port);
  if (connect(sok, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    return (-1);
  clt->data.sock = sok;
  return (0);
}
