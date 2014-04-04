/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#include <string.h>

#include "struct_client.h"
#include "xmalloc.h"
#include "client_command.h"
#include "client_command_transfert.h"
#include "client_command_list.h"
#include "client_command_put.h"
#include "client_command_get.h"
#include "local_cmd.h"

t_cmd		*add_node(const char *cmd, cmd_ptr ptr)
{
  t_cmd		*cur;

  cur = (t_cmd*)xmalloc(sizeof(*cur));
  cur->cmd = strdup(cmd);
  cur->ptr = ptr;
  cur->next = NULL;
  return (cur);
}

void		load_lexer_local(t_cmd *cur)
{
  cur->next = add_node("lls", &local_cmd_ls);
  cur = cur->next;
  cur->next = add_node("lpwd", &local_cmd_pwd);
  cur = cur->next;
  cur->next = add_node("lcd", &local_cmd_cd);
}

t_cmd		*load_client_lexer(void)
{
  t_cmd		*lexer;
  t_cmd		*cur;

  lexer = add_node("cd", &cmd_cd);
  cur = lexer;
  cur->next = add_node("quit", &cmd_quit);
  cur = cur->next;
  cur->next = add_node("exit", &cmd_quit);
  cur = cur->next;
  cur->next = add_node("pwd", &cmd_pwd);
  cur = cur->next;
  cur->next = add_node("sendport", &cmd_sendport);
  cur = cur->next;
  cur->next = add_node("passiv", &cmd_passiv);
  cur = cur->next;
  cur->next = add_node("ls", &cmd_list);
  cur = cur->next;
  cur->next = add_node("get", &client_command_get);
  cur = cur->next;
  cur->next = add_node("put", &client_command_put);
  load_lexer_local(cur->next);
  return (lexer);
}
