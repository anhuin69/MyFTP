/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#ifndef		LOCAL_CMD_H_
# define	LOCAL_CMD_H_

void		local_cmd_cd(struct_client *clt);
void		local_cmd_pwd(struct_client *clt);
void		local_cmd_ls(struct_client *clt);

#endif
