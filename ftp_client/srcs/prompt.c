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
#include <unistd.h>
#include <string.h>

static void	my_putstr(const char *str)
{
  write(1, str, strlen(str));
}

void		prompt()
{
  my_putstr("my_ftp> ");
}
