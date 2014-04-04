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
#include <string.h>
#include <stdio.h>

#include "struct_client.h"

int		sread(struct_client *clt)
{
  int		r;
  int		i;

  bzero(clt->buffer, MAX_READ + 1);
  if ((r = read(clt->sock, clt->buffer, MAX_READ)) <= 0)
    {
      clt->is_connected = FALSE;
      clt->error = ERR_READ;
      return (-1);
    }
  for (i = 0; i < r; i++)
    if (clt->buffer[i] == '\n' || clt->buffer[i] == '\r')
      clt->buffer[i] = '\0';
  return (r);
}
