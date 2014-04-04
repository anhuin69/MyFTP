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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "struct_client.h"
#include "ftp_data.h"
#include "sread.h"

int		send_port_to_serv(struct_client *clt, char *a1)
{
  char		*a2;
  char		*a3;
  char		*a4;
  int		oldfd;

  a2 = strstr(a1, ".");
  a2[0] = '\0';
  a2++;
  a3 = strstr(a2, ".");
  a3[0] = '\0';
  a3++;
  a4 = strstr(a3, ".");
  a4[0] = '\0';
  a4++;
  oldfd = dup(1);
  dup2(clt->sock, 1);
  printf("PORT %s,%s,%s,%s,%d,%d\n", a1, a2, a3, a4,
	 clt->data.port / 256, clt->data.port % 256);
  dup2(oldfd, 1);
  return (0);
}

int		active_mode(struct_client *clt)
{
  char		*a1;

  if (new_data_chan(&(clt->data)) == -1)
    {
      printf("error : impossible to create data socket\n");
      return (-1);
    }
  clt->data.transfert_mode = PASV;
  a1 = strdup(clt->data.ip);
  send_port_to_serv(clt, a1);
  free(a1);
  sread(clt);
  printf("%s\n", clt->buffer);
  return (0);
}
