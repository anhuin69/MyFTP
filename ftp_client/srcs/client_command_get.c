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
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include "struct_client.h"
#include "count_parameters.h"
#include "client_command_transfert.h"
#include "sread.h"
#include "swrite.h"
#include "ftp_data.h"
#include "client_active_mode.h"

const char	*get_active(struct_client *clt, char *file, int r)
{
  int		nsock;
  char		buff[MAX_READ + 1];
  char		cmd[MAX_READ + 1];
  int		fd;

  bzero(cmd, MAX_READ + 1);
  strcat(cmd, "RETR ");
  strcat(cmd, file);
  strcat(cmd, "\n");
  swrite(clt, cmd);
  sread(clt);
  printf("%s\n", clt->buffer);
  if ((nsock = accept_data_client(clt)) == -1)
    return ("error : connection with server failed");
  if (strstr(clt->buffer, "520") == clt->buffer)
    return (clt->buffer);
  if ((fd = creat(file, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return ("error : error creating file");
  while ((r = read(nsock, buff, MAX_READ)) > 0)
    if (write(fd, buff, r) == -1)
      break ;
  close_data_chan(clt, nsock);
  sread(clt);
  close(fd);
  return (clt->buffer);
}

const char	*get_passiv(struct_client *clt, char *file)
{
  int		fd;
  char		buff[MAX_READ + 1];
  char		cmd[MAX_READ + 1];
  int		r;

  if (connect_to_client(clt) == -1)
    return ("error : impossible to reach server");
  bzero(cmd, MAX_READ + 1);
  strcat(cmd, "RETR ");
  strcat(cmd, file);
  strcat(cmd, "\n");
  swrite(clt, cmd);
  sread(clt);
  if (strstr(clt->buffer, "520") == clt->buffer)
    return (clt->buffer);
  if ((fd = creat(file, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return ("error : error creating file");
  printf("%s\n", clt->buffer);
  while ((r = read(clt->data.sock, buff, MAX_READ)) > 0)
    if (write(fd, buff, r) == -1)
      break ;
  close_data_chan(clt, -1);
  sread(clt);
  close(fd);
  return (clt->buffer);
}

void		client_command_get(struct_client *clt)
{
  char		*file;
  const char	*ptr;

  ptr = NULL;
  if (count_parameters(clt->buffer) != 2)
    {
      printf("error : command get takes one parameter\n");
      return ;
    }
  file = strdup(&(clt->buffer[4]));
  file[strlen(file) - 1] = '\0';
  if (clt->data.transfert_mode == PASV)
    {
      if (mode_passiv(clt) == 0)
	ptr = get_passiv(clt, file);
    }
  else if (clt->data.transfert_mode == PORT)
    {
      if (active_mode(clt) == 0)
	ptr = get_active(clt, file, 0);
    }
  else
    printf("error : specify a transfert mode (passiv or sendport)\n");
  free(file);
  printf("%s\n", ptr);
}
