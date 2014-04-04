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

#include "server_error.h"

void		*xmalloc(size_t size)
{
  void		*ptr;

  if ((ptr = malloc(size)) == NULL)
    server_error("malloc failed");
  return (ptr);
}
