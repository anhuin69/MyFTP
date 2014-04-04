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

char		*go_next_word(char *str)
{
  char		*ptr;
  int		i;

  for (i = 0; str[i] && str[i] != ' ' && str[i] != '\t'; i++);
  while (str[i] && (str[i] == ' ' || str[i] == '\t'))
    i++;
  ptr = str + i;
  if (ptr[0] == '\0' || ptr[0] == '\n')
    return (NULL);
  return (ptr);
}

int		count_parameters(char *str)
{
  int		nbr;
  char		*ptr;

  if (str[0] == '\0' || str[0] == '\n')
    return (0);
  ptr = str;
  nbr = 0;
  while (ptr != NULL)
    {
      ptr = go_next_word(ptr);
      nbr++;
    }
  return (nbr);
}
