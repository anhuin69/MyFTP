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
#include <string.h>

void		epure_str(char *str)
{
  int		i;
  int		nbr;

  for (i = 0; str && str[i] && (str[i] == ' ' || str[i] == '\t'); i++);
  if (i > 0)
    {
      nbr = strlen(str + i);
      memmove(str, str + i, strlen(str + i));
      str[nbr] = '\0';
    }
  i = 0;
  while (str[i] && str[i + 1])
    {
      if ((str[i] == ' ' || str[i] == '\t')
	  && (str[i + 1] == ' ' || str[i + 1] == '\t'))
	{
	  nbr = strlen(str + i + 1);
	  memmove(str + i, str + i + 1, nbr);
	  str[nbr + i] = '\0';
	  i = 0;
	}
      else
	i++;
    }
}
