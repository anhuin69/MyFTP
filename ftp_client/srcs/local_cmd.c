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
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "struct_client.h"
#include "count_parameters.h"

void		local_cmd_ls(struct_client *clt)
{
  (void)clt;
  system("ls -l");
}

void		local_cmd_pwd(struct_client *clt)
{
  (void)clt;
  system("pwd");
}

void		local_cmd_cd(struct_client *clt)
{
  if (count_parameters(clt->buffer) != 2)
    {
      printf("error : lcd takes one parameter\n");
      return ;
    }
  clt->buffer[strlen(clt->buffer) - 1] = '\0';
  if (chdir(&(clt->buffer[4])) == -1)
    printf("error : %s\n", strerror(errno));
}
