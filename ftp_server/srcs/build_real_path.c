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
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "struct_client.h"
#include "xmalloc.h"

char		*build_real_path(struct_client *clt)
{
  char		*dist_path;
  char		*real_path;

  dist_path = strstr(clt->buffer, " ");
  if (dist_path == NULL)
    return (NULL);
  dist_path++;
  if (dist_path[0] != '/')
    return (strdup(dist_path));
  real_path = (char*)xmalloc(PATH_MAX_LENGHT);
  bzero(real_path, PATH_MAX_LENGHT);
  real_path = strcat(real_path, clt->root_path);
  real_path = strcat(real_path, dist_path);
  return (real_path);
}
