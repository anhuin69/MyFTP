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

int		xdup(int oldfd)
{
  int		fd;

  fd = dup(oldfd);
  if (fd == -1)
    exit(EXIT_FAILURE);
  return (fd);
}

int		xdup2(int oldfd, int newfd)
{
  int		fd;

  fd = dup2(oldfd, newfd);
  if (newfd == -1)
    exit(EXIT_FAILURE);
  return (fd);
}

int		xclose(int fd)
{
  if (close(fd) == -1)
    exit(EXIT_FAILURE);
  return (0);
}
