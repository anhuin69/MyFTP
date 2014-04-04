/*
** file.c for  in /home/bascou_f/work/my_ftp
** 
** Made by fabrice bascoulergue
** Login   <bascou_f@epitech.net>
** 
** Started on  Thu Feb 10 18:44:13 2011 fabrice bascoulergue
** Last update Thu Feb 10 18:44:14 2011 fabrice bascoulergue
*/

#ifndef		SERVER_ERROR_H_
# define	SERVER_ERROR_H_

# define ERR_SCREATE	"Could not create server socket"
# define ERR_SBIND	"Could not bind to port."
# define ERR_SLISTEN	"Could not listen to socket."
# define ERR_SACCEPT	"Could not accept socket."
# define ERR_SWRITE	"Could not write to socket."
# define ERR_SREAD	"Could not read to socket."

void		server_error(const char*);

#endif
