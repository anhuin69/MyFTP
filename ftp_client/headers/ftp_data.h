/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#ifndef		FTP_DATA_H_
# define	FTP_DATA_H

int		new_data_chan(t_data *data);
void		close_data_chan(struct_client *clt, int sock);
int		accept_data_client(struct_client *clt);
int		connect_to_client(struct_client *clt);

#endif
