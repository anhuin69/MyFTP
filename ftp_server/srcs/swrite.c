/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#include <string.h>
#include <unistd.h>

#include "struct_client.h"

int		swrite(struct_client *clt, const char *buff)
{
  int		r;

  if ((r = write(clt->sock, buff, strlen(buff))) == -1)
    {
      clt->is_connected = FALSE;
      clt->error = ERR_WRITE;
      return (-1);
    }
  return (r);
}
