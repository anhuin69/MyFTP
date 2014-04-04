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
#include <strings.h>
#include <string.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "struct_client.h"
#include "swrite.h"
#include "client_request.h"

void		init_root_path(struct_client *clt)
{
  if (access(SERV_ROOT_DIR, F_OK | R_OK | W_OK) == -1)
    {
      clt->is_connected = FALSE;
      clt->error = ERR_CONTEXT;
      return ;
    }
  chdir(SERV_ROOT_DIR);
  bzero(clt->root_path, PATH_MAX_LENGHT);
  if (getcwd(clt->root_path, PATH_MAX_LENGHT) == NULL)
    {
      clt->is_connected = FALSE;
      clt->error = ERR_CONTEXT;
    }
}

void		init_data_connection(struct_client *clt)
{
  char		ac[256];
  struct hostent *phe;
  struct in_addr locaddr;

  gethostname(ac, sizeof(ac));
  phe = gethostbyname(ac);
  memcpy(&locaddr, phe->h_addr_list[0], sizeof(struct in_addr));
  strcpy(clt->data.ip, inet_ntoa(locaddr));
  clt->data.sock = -1;
  clt->data.port = -1;
  clt->data.transfert_mode = UNSET;
}

void		init_client(struct_client *clt, int sock)
{
  init_data_connection(clt);
  clt->sock = sock;
  clt->error = NULL;
  clt->is_logged = NOT_LOG;
  clt->file_to_rename = NULL;
  if (sock >= 0)
    clt->is_connected = TRUE;
  else
    {
      clt->is_connected = FALSE;
      clt->error = ERR_TIMEOUT;
    }
  init_root_path(clt);
  swrite(clt, "220 Hello.\n");
  printf("New client connected.\n");
}

void		init_select(struct_client *clt)
{
  FD_ZERO(&(clt->fs));
  FD_SET(clt->sock, &(clt->fs));
  clt->tm.tv_sec = PING_DELAY;
  clt->tm.tv_usec = 0;
}

void		fork_client(int sock, t_cmd *cmd_lexer, int ret)
{
  struct_client	clt;

  init_client(&clt, sock);
  while (clt.is_connected == TRUE)
    {
      init_select(&clt);
      if ((ret = select(clt.sock + 1, &(clt.fs), NULL, NULL, &(clt.tm))) == -1)
	{
	  clt.is_connected = FALSE;
	  clt.error = ERR_SELECT;
	}
      else if (ret > 0)
	client_request(&clt, cmd_lexer);
      else
	{
	  clt.is_connected = FALSE;
	  clt.error = ERR_TIMEOUT;
	}
    }
  if (clt.error != NULL)
    printf("%s on socket %d.\n", clt.error, clt.sock);
  else
    printf("Unknonwn error.\n");
  close(clt.sock);
  exit(EXIT_SUCCESS);
}
