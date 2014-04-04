/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#include <stdio.h>
#include <stdlib.h>

#include "server_error.h"

void		server_error(const char *str)
{
  printf("Error : %s\n", str);
  exit(EXIT_FAILURE);
}
