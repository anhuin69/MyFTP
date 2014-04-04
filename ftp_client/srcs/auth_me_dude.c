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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "struct_client.h"
#include "client_error.h"
#include "sread.h"
#include "swrite.h"

void		my_putstr(const char *str)
{
  if (write(1, str, strlen(str)) == -1)
    client_error("write failed on standard ouput");
}

int		auth_user(struct_client *clt)
{
  char		buff[MAX_READ + 1];

  my_putstr("Name : ");
  bzero(buff, MAX_READ + 1);
  if (read(0, buff, MAX_READ) == -1)
    client_error("read on standard input fail");
  if (buff[0] == '\n')
    return (FALSE);
  bzero(clt->buffer, MAX_READ + 1);
  strcat(clt->buffer, "USER ");
  strcat(clt->buffer, buff);
  strcat(clt->buffer, "\n");
  swrite(clt, clt->buffer);
  sread(clt);
  printf("%s\n", clt->buffer);
  if (strstr(clt->buffer, "530"))
    return (FALSE);
  return (TRUE);
}

int		auth_pass(struct_client *clt)
{
  char		buff[MAX_READ + 1];

  my_putstr("Password : ");
  bzero(buff, MAX_READ + 1);
  if (read(0, buff, MAX_READ) == -1)
    client_error("read on standard input fail");
  if (buff[0] == '\n')
    return (FALSE);
  bzero(clt->buffer, MAX_READ + 1);
  strcat(clt->buffer, "PASS ");
  strcat(clt->buffer, buff);
  strcat(clt->buffer, "\n");
  swrite(clt, clt->buffer);
  sread(clt);
  printf("%s\n", clt->buffer);
  if (strstr(clt->buffer, "530"))
    return (FALSE);
  return (TRUE);
}

void		auth_me_dude(struct_client *clt)
{
  if (auth_user(clt) == FALSE)
    {
      printf("Login failed, please enter a correct login\n");
      auth_me_dude(clt);
      return ;
    }
  if (auth_pass(clt) == FALSE)
    {
      printf("Bad login and password combinaison\n");
      auth_me_dude(clt);
      return ;
    }
}
