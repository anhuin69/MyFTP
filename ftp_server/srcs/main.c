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

#include "ftp_server.h"

int		main(int ac, char **av)
{
  if (ac < 2)
    printf("%s: Usage : %s port\n", av[0], av[0]);
  else
    ftp_server(atoi(av[1]));
  return (0);
}
