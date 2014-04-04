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
#include <stdio.h>
#include <string.h>

#include "struct_client.h"
#include "sread.h"
#include "swrite.h"
#include "xfunc.h"

void		client_request(struct_client *clt, t_cmd *lexer)
{
  t_cmd		*cur;
  int		r;
  int		fdout;
  int		cdone;

  cdone = FALSE;
  fdout = xdup(1);
  xdup2(clt->sock, 1);
  if ((r = sread(clt)) <= 0)
    return ;
  cur = lexer;
  while (cur != NULL)
    {
      if (strstr(clt->buffer, cur->cmd))
	{
	  cur->ptr(clt);
	  cdone = TRUE;
	  break ;
	}
      cur = cur->next;
    }
  xdup2(fdout, 1);
  if (cdone == FALSE)
    swrite(clt, "500 Command not understood.\n");
}
