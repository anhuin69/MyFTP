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
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>

#include "struct_client.h"
#include "ftp_data.h"
#include "build_real_path.h"

int		passiv_retr_file(struct_client *clt, char *name)
{
  char		buff[MAX_READ + 1];
  int		oldfd;
  int		nsock;
  int		filedesc;
  int		r;

  printf("150 Opening BINARY mode data connection\n");
  if ((nsock = accept_data_client(clt)) == -1)
    return (-1);
  oldfd = dup(1);
  dup2(nsock, 1);
  if ((filedesc = open(name, O_RDONLY)) == -1)
    return (-1);
  while ((r = read(filedesc, buff, MAX_READ)) > 0)
    {
      if (write(nsock, buff, r) == -1)
	return (-1);
    }
  close(filedesc);
  dup2(oldfd, 1);
  printf("226 Transfer complete\n");
  close_data_chan(clt, nsock);
  return (0);
}

int		port_retr_file(struct_client *clt, char *name)
{
  char		buff[MAX_READ + 1];
  int		oldfd;
  int		filedesc;
  int		r;

  printf("150 Opening BINARY mode data connection\n");
  if (connect_to_client(clt) == -1)
    return (-1);
  oldfd = dup(1);
  dup2(clt->data.sock, 1);
  if ((filedesc = open(name, O_RDONLY)) == -1)
    return (-1);
  while ((r = read(filedesc, buff, MAX_READ)) > 0)
    {
      if (write(clt->data.sock, buff, r) == -1)
	return (-1);
    }
  close(filedesc);
  dup2(oldfd, 1);
  printf("226 Transfer complete\n");
  close_data_chan(clt, -1);
  return (0);
}

void		cmd_retr(struct_client *clt)
{
  char		*name;
  int		ret;

  ret = 0;
  if ((name = build_real_path(clt)) == NULL)
    {
      printf("550 RETR please specify a file to retrieve\n");
      return ;
    }
  if (clt->data.transfert_mode == UNSET)
    {
      printf("520 RETR you have to use PORT or PASV before\n");
      return ;
    }
  if (clt->data.transfert_mode == PASV)
    ret = passiv_retr_file(clt, name);
  else if (clt->data.transfert_mode == PORT)
    ret = port_retr_file(clt, name);
  if (ret == -1)
    printf("520 File not found\n");
}
