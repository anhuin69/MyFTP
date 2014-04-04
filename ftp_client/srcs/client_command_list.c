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
#include <stdio.h>

#include "struct_client.h"
#include "count_parameters.h"
#include "client_command_transfert.h"
#include "sread.h"
#include "swrite.h"
#include "ftp_data.h"
#include "client_active_mode.h"

void		list_passiv(struct_client *clt)
{
  char		buff[MAX_READ + 1];
  int		r;

  swrite(clt, "LIST\n");
  sread(clt);
  printf("%s\n", clt-> buffer);
  if (connect_to_client(clt) == -1)
    {
      printf("error : impossible to reach server\n");
      return ;
    }
  while ((r = read(clt->data.sock, buff, MAX_READ)) > 0)
    {
      buff[r] = '\0';
      write(1, buff, r);
    }
  sread(clt);
  close_data_chan(clt, -1);
  printf("%s\n", clt->buffer);
}

void		list_active(struct_client *clt)
{
  int		nsock;
  int		r;
  char		buff[MAX_READ + 1];

  swrite(clt, "LIST\n");
  sread(clt);
  printf("%s\n", clt->buffer);
  if ((nsock = accept_data_client(clt)) == -1)
    {
      printf("error : connection with server failed\n");
      return ;
    }
  while ((r = read(nsock, buff, MAX_READ)) > 0)
    {
      buff[r] = '\0';
      printf("%s", buff);
    }
  sread(clt);
  printf("%s\n", clt->buffer);
  close_data_chan(clt, nsock);
}

void		cmd_list(struct_client *clt)
{
  if (count_parameters(clt->buffer) != 1)
    {
      printf("error : Too many parameters for command ls\n");
      return ;
    }
  if (clt->data.transfert_mode == PASV)
    {
      if (mode_passiv(clt) == 0)
	list_passiv(clt);
    }
  else if (clt->data.transfert_mode == PORT)
    {
      if (active_mode(clt) == 0)
	list_active(clt);
    }
  else
    printf("error : specify a transfert mode (passiv or sendport)\n");
}
