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
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "struct_client.h"
#include "swrite.h"
#include "build_real_path.h"

void		cmd_cwd(struct_client *clt)
{
  char		wd[PATH_MAX_LENGHT];
  char		*path;

  path = build_real_path(clt);
  if (path == NULL)
    return ;
  if (chdir(path) == -1)
    {
      printf("550 %s\n", strerror(errno));
      free(path);
      return ;
    }
  bzero(wd, PATH_MAX_LENGHT);
  getcwd(wd, PATH_MAX_LENGHT);
  if (strlen(wd) < strlen(clt->root_path))
    {
      chdir(clt->root_path);
      printf("550 Acces denied\n");
    }
  else
    printf("250 CWD command successful\n");
  free(path);
}

void		cmd_cdup(struct_client *clt)
{
  char		wd[PATH_MAX_LENGHT];

  if (chdir("..") == -1)
    {
      printf("550 %s\n", strerror(errno));
      return ;
    }
  bzero(wd, PATH_MAX_LENGHT);
  getcwd(wd, PATH_MAX_LENGHT);
  if (strlen(wd) < strlen(clt->root_path))
    {
      chdir(clt->root_path);
      printf("550 Acces denied\n");
    }
  else
    printf("250 CDUP command successful\n");
}

void		cmd_pwd(struct_client *clt)
{
  char		wd[PATH_MAX_LENGHT];
  char		*distPath;

  bzero(wd, PATH_MAX_LENGHT);
  if ((distPath = getcwd(wd, PATH_MAX_LENGHT)) == NULL)
    printf("550 %s\n", strerror(errno));
  else
    {
      distPath += strlen(clt->root_path);
      if (distPath[0] == '\0')
      	distPath[0] = '/';
      printf("257 \"%s\" is the current directory\n", distPath);
    }
}
