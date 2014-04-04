/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "struct_client.h"
#include "count_parameters.h"
#include "swrite.h"
#include "sread.h"

int		build_port(char *port)
{
  int		nbr1;
  int		nbr2;
  int		i;

  nbr1 = atoi(port);
  for (i = 0; port[i]; i++)
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
  for (i = 0; addr[i] && addr[i] != ')'; i++)
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

int		mode_passiv(struct_client *clt)
{
  char		*addr;

  swrite(clt, "PASV\n");
  sread(clt);
  printf("%s\n", clt->buffer);
  if ((addr = strstr(clt->buffer, "(")) == NULL)
    {
      printf("error : bad informations recieved from server\n");
      return (-1);
    }
  addr++;
  if (fill_data(clt, addr) == -1)
    {
      printf("error : bad informations recieved from server\n");
      return (-1);
    }
  return (0);
}

void		cmd_passiv(struct_client *clt)
{
  if (clt->data.transfert_mode != PASV)
    {
      printf("passiv mode on.\n");
      clt->data.transfert_mode = PASV;
    }
  else
    {
      printf("passiv mode off\n");
      clt->data.transfert_mode = PORT;
    }
}

void		cmd_sendport(struct_client *clt)
{
  if (clt->data.transfert_mode != PORT)
    {
      printf("active mode on.\n");
      clt->data.transfert_mode = PORT;
    }
  else
    {
      printf("active mode off.\n");
      clt->data.transfert_mode = PASV;
    }
}

