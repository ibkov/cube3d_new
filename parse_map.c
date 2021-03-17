# include "includes/cube3d.h"

void full_new_line(char *buffer, char *new_str)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (buffer[i])
  {
    if (buffer[i] != ' ')
    {
      new_str[j] = buffer[i];
      j++;
    }
    i++;
  }
  new_str[j] = '\0';
}

char *cor_start_ch(char *buffer)
{
  int i;
  int cs;
  char *new_str;

  i = 0;
  cs = 0;
  while (buffer[i])
  {
    if (buffer[i] == ' ')
      cs++;
    i++;
  }
  if (!(new_str = (char*)malloc(sizeof(char) * (ft_strlen(buffer) - cs + 1))))
    return (NULL);
  full_new_line(buffer, new_str);
  return (new_str);
}