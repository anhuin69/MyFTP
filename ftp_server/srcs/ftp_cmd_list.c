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
#include "xfunc.h"

void		list_passiv(struct_client *clt)
{
  int		oldfd;
  int		nsock;

  printf("150 Opening BINARY mode data connection for 'ls'\n");
  if ((nsock = accept_data_client(clt)) == -1)
    {
      printf("520 LIST impossible to reach client\n");
      return ;
    }
  oldfd = xdup(1);
  xdup2(nsock, 1);
  system("ls -la");
  xdup2(oldfd, 1);
  printf("226 Transfer complete\n");
  close_data_chan(clt, nsock);
}

void		cmd_list(struct_client *clt)
{
  int		oldfd;

  if (clt->data.transfert_mode == UNSET)
    {
      printf("520 LIST you have to use PORT or PASV before\n");
      return ;
    }
  if (clt->data.transfert_mode == PASV)
    list_passiv(clt);
  else if (clt->data.transfert_mode == PORT)
    {
      printf("150 Opening BINARY mode data connection for 'ls'\n");
      if (connect_to_client(clt) == -1)
	{
	  printf("520 LIST impossible to reach client\n");
	  return ;
	}
      oldfd = xdup(1);
      xdup2(clt->data.sock, 1);
      system("ls -la");
      xdup2(oldfd, 1);
      printf("226 Transfer complete\n");
      close_data_chan(clt, -1);
    }
}
