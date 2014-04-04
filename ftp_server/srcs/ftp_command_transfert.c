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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>

#include "struct_client.h"
#include "ftp_data.h"
#include "build_real_path.h"

void		cmd_pasv(struct_client *clt)
{
  char		*a1;
  char		*a2;
  char		*a3;
  char		*a4;

  if (new_data_chan(&(clt->data)) == -1)
    {
      printf("520 PASV impossible to create data socket\n");
      return ;
    }
  clt->data.transfert_mode = PASV;
  a1 = strdup(clt->data.ip);
  a2 = strstr(a1, ".");
  a2[0] = '\0';
  a2++;
  a3 = strstr(a2, ".");
  a3[0] = '\0';
  a3++;
  a4 = strstr(a3, ".");
  a4[0] = '\0';
  a4++;
  printf("227 Entering Passive Mode (%s,%s,%s,%s,%d,%d)\n", a1, a2, a3, a4,
	 clt->data.port / 256, clt->data.port % 256);
  free(a1);
}

int		build_port(char *port)
{
  int		nbr1;
  int		nbr2;
  int		i;

  nbr1 = atoi(port);
  for (i = 0; port[i] && port[i]; i++)
    if (port[i] == ',')
      {
	port = port + i + 1;
	break ;
      }
  nbr2 = atoi(port);
  return (nbr1 * 256 + nbr2);
}

int		fill_data(struct_client *clt, char *addr)
{
  int		i;
  int		cnt;

  cnt = 0;
  for (i = 0; addr[i] && addr[i] != ' '; i++)
    {
      if (addr[i] == ',')
	{
	  cnt++;
	  addr[i] = '.';
	}
      if (cnt == 4)
	break ;
    }
  strncpy(clt->data.ip, addr, i);
  clt->data.ip[i] = '\0';
  addr += i;
  if (addr[0] == '\0')
    return (-1);
  if ((clt->data.port = build_port(addr + 1)) == 0)
    return (-1);
  return (0);
}

void		cmd_port(struct_client *clt)
{
  char		*addr;

  if ((addr = strstr(clt->buffer, " ")) == NULL)
    {
      printf("520 PORT please specify an ip adress an a port number\n");
      return ;
    }
  addr++;
  if (fill_data(clt, addr) == -1)
    {
      printf("520 PORT please specify an ip adress an a port number\n");
      return ;
    }
  clt->data.transfert_mode = PORT;
  clt->data.sock = -1;
  printf("220 Entering active mode\n");
}
