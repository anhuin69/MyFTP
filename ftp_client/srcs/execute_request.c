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
#include <string.h>

#include "struct_client.h"
#include "swrite.h"
#include "sread.h"
#include "epure_str.h"

int		compare_cmd(char *buff, char * cmd)
{
  int		end;
  if (strstr(buff, cmd) != buff)
    return (-1);
  end = strlen(cmd);
  if (buff[end] != '\0' && buff[end] != ' ' && buff[end] != '\n')
    return (-1);
  return (0);
}

void		execute_request(struct_client *clt, t_cmd *lexer)
{
  t_cmd		*cur;

  cur = lexer;
  while (cur != NULL)
    {
      if (compare_cmd(clt->buffer, cur->cmd) == 0)
	{
	  cur->ptr(clt);
	  return ;
	}
      cur = cur->next;
    }
  printf("Invalid command\n");
}
