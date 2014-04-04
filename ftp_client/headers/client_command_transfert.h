/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#ifndef		CLIENT_COMMAND_TRANSFERT_H_
# define	CLIENT_COMMAND_TRANSFERT_H_

int		mode_passiv(struct_client *clt);
void		cmd_passiv(struct_client *clt);
void		cmd_sendport(struct_client *clt);

#endif
