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
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

#include "struct_client.h"
#include "build_real_path.h"

void		cmd_rnfr(struct_client *clt)
{
  char		*name;

  name = build_real_path(clt);
  if (name == NULL)
    {
      printf("550 RNFR File not found\n");
      return ;
    }
  if (access(name, F_OK | R_OK | W_OK) == -1)
    printf("550 RNFR %s\n", strerror(errno));
  else
    {
      printf("257 RNFR command successful\n");
      clt->file_to_rename = strdup(name);
    }
  free(name);
}

void		cmd_rnto(struct_client *clt)
{
  char		*new_name;

  if (clt->file_to_rename == NULL)
    {
      printf("550 RNTO please specify a file to rename with RNFR\n");
      return ;
    }
  if ((new_name = build_real_path(clt)) == NULL)
    {
      printf("550 RNTO missing name parameter\n");
      return ;
    }
  if (rename(clt->file_to_rename, new_name) == -1)
    printf("550 RNTO %s\n", strerror(errno));
  else
    printf("257 RNTO command successful\n");
  free(new_name);
  free(clt->file_to_rename);
  clt->file_to_rename = NULL;
}

void		cmd_dele(struct_client *clt)
{
  char		*name;

  if ((name = build_real_path(clt)) == NULL)
    {
      printf("550 please specify a file to remove\n");
      return ;
    }
  if (remove(name) == -1)
    printf("550 %s\n", strerror(errno));
  else
    printf("257 DELE command successful\n");
  free(name);
}

void		cmd_rmd(struct_client *clt)
{
  cmd_dele(clt);
}

void		cmd_mkd(struct_client *clt)
{
  char		*name;

  if ((name = build_real_path(clt)) == NULL)
    {
      printf("550 pleasye specify a name for the new folder\n");
      return ;
    }
  if (mkdir(name, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == -1)
    printf("550 %s\n", strerror(errno));
  else
    printf("257 MKD command successful\n");
  free(name);
}

