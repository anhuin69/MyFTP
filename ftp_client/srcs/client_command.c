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
#include "count_parameters.h"
#include "swrite.h"
#include "sread.h"

void		cmd_cd(struct_client *clt)
{
  char		build[MAX_READ + 1];

  if (count_parameters(clt->buffer) != 2)
    {
      printf("error : commmand cd takes one parameter\n");
      return ;
    }
  bzero(build, MAX_READ);
  strcat(build, "CWD ");
  strcat(build, clt->buffer + 3);
  swrite(clt, build);
  sread(clt);
  printf("%s\n", clt->buffer);
}

void		cmd_pwd(struct_client *clt)
{
  if (count_parameters(clt->buffer) != 1)
    {
      printf("error : too many parameters for command pwd\n");
      return ;
    }
  swrite(clt, "PWD\n");
  sread(clt);
  printf("%s\n", clt->buffer);
}

void		cmd_quit(struct_client *clt)
{
  swrite(clt, "QUIT\n");
  sread(clt);
  printf("%s\n", clt->buffer);
  clt->is_connected = FALSE;
}
