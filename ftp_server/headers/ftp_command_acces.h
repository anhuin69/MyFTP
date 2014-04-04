/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#ifndef		FTP_COMMAND_ACCES_H_
# define	FTP_COMMAND_ACCES_H_

void		cmd_noop(struct_client *clt);
void		cmd_user(struct_client *clt);
void		cmd_pass(struct_client *clt);
void		cmd_quit(struct_client *clt);
void		cmd_type(struct_client *clt);

#endif
