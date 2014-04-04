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

#include "ftp_client.h"
#include "epure_str.h"

int		main(int ac, char **av)
{
  if (ac < 3)
    printf("Usage : ./client machine port\n");
  else
    ftp_client(av[1], atoi(av[2]));
  return (0);
}
