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
#include <stdio.h>

#include "xmalloc.h"
#include "struct_client.h"
#include "ftp_command_acces.h"
#include "ftp_command_move.h"
#include "ftp_command_file.h"
#include "ftp_command_transfert.h"
#include "ftp_cmd_retr.h"
#include "ftp_cmd_stor.h"
#include "ftp_cmd_list.h"

t_cmd		*add_node(const char *cmd, cmd_ptr ptr)
{
  t_cmd		*cur;

  cur = (t_cmd*)xmalloc(sizeof(*cur));
  cur->cmd = (char*)xmalloc(17);
  strcpy(cur->cmd, cmd);
  cur->ptr = ptr;
  cur->next = NULL;
  return (cur);
}

t_cmd		*load_command_move(t_cmd *cur)
{
  cur->next = add_node("CWD", &cmd_cwd);
  cur = cur->next;
  cur->next = add_node("CDUP", &cmd_cdup);
  cur = cur->next;
  cur->next = add_node("PWD", &cmd_pwd);
  return (cur->next);
}

t_cmd		*load_command_file(t_cmd *cur)
{
  cur->next = add_node("RNFR", &cmd_rnfr);
  cur = cur->next;
  cur->next = add_node("RNTO", &cmd_rnto);
  cur = cur->next;
  cur->next = add_node("DELE", &cmd_dele);
  cur = cur->next;
  cur->next = add_node("RMD", &cmd_rmd);
  cur = cur->next;
  cur->next = add_node("MKD", &cmd_mkd);
  return (cur->next);
}

t_cmd		*load_command_transfert(t_cmd *cur)
{
  cur->next = add_node("PASV", &cmd_pasv);
  cur = cur->next;
  cur->next = add_node("PORT", &cmd_port);
  cur = cur->next;
  cur->next = add_node("RETR", &cmd_retr);
  cur = cur->next;
  cur->next = add_node("STOR", &cmd_stor);
  cur = cur->next;
  cur->next = add_node("LIST", &cmd_list);
  return (cur->next);
}

t_cmd		*load_lexer()
{
  t_cmd		*lexer;
  t_cmd		*cur;

  lexer = add_node("NOOP", &cmd_noop);
  cur = lexer;
  cur->next = add_node("USER", &cmd_user);
  cur = cur->next;
  cur->next = add_node("PASS", &cmd_pass);
  cur = cur->next;
  cur->next = add_node("QUIT", &cmd_quit);
  cur = cur->next;
  cur->next = add_node("TYPE", &cmd_type);
  cur = cur->next;
  cur = load_command_move(cur);
  cur = load_command_file(cur);
  cur = load_command_transfert(cur);
  return (lexer);
}
