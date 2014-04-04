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

#include "struct_client.h"
#include "swrite.h"

void		cmd_noop(struct_client *clt)
{
  swrite(clt, "OK\n");
}

void		cmd_user(struct_client *clt)
{
  if (strstr(clt->buffer, "anonymous") == NULL)
    swrite(clt, "530 This FTP server is anonymous only.\n");
  else
    {
      clt->is_logged = LOGGED;
      swrite(clt, "331 Please specify password.\n");
    }
}

void		cmd_pass(struct_client *clt)
{
  if (clt->is_logged == LOGGED)
    {
      clt->is_logged = AUTH;
      swrite(clt, "230 Guest login ok.\n");
    }
  else
    swrite(clt, "503 Login with USER first.\n");
}

void		cmd_quit(struct_client *clt)
{
  swrite(clt, "221 Goodbye.\n");
  clt->is_connected = FALSE;
  clt->error = CLIENT_QUIT;
}

void		cmd_type(struct_client *clt)
{
  char		*type;

  if ((type = strstr(clt->buffer, " ")) == NULL)
    {
      printf("500 TYPE please specify a type\n");
      return ;
    }
  type++;
  if (strcmp(type, "I") != 0 && strcmp(type, "A") != 0)
    {
      printf("500 TYPE this server only accept type I\n");
      return ;
    }
  printf("200 Type set to %s\n", type);
}
