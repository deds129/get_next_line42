/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanisha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:26:02 by hanisha           #+#    #+#             */
/*   Updated: 2020/11/24 16:26:21 by hanisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "get_next_line.h"
//gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c
// get_next_line_utils.c



//метод очищающий строку переводящий все байты в строки в ноль без аллокации
// памяти
void	ft_bzero(char *s)
{
	size_t i;

	i = 0;
	if(s != NULL)
		while (s[i])
		{
			((char *)s)[i] = 0;
			i++;
		}
}
char *remainer_check(char *remainer, char **line)
{
	char *p_nextline;

	p_nextline = NULL;
	if (remainer)
		if ((p_nextline = (ft_strchr(remainer,'\n'))))
		{
			*p_nextline = '\0';
			*line = ft_strdup(remainer);
			p_nextline++;
			ft_strcpy(remainer,p_nextline);
		}
		else
			{
				*line = ft_strdup(remainer);
				ft_bzero(remainer);
			}
	else
		*line = ft_strdup("");
	return (p_nextline);
}

int	get_next_line(int fd, char **line)
{
	char				*buff;
	int					read_byte;
	static char 		*remainer;
	char				*p_nextline;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if(!(buff = (char *)(malloc(sizeof(char) * BUFFER_SIZE + 1))))
		return (-1);

	p_nextline = remainer_check(remainer,line);

	while (!p_nextline && (read_byte = read(fd,buff,BUFFER_SIZE)))
	{
		buff[read_byte] = '\0';
		if((p_nextline = (ft_strchr(buff,'\n'))))
		{
			*p_nextline = '\0';
			p_nextline++;
			remainer = ft_strdup(p_nextline);
		}
		*line = ft_strjoin(*line,buff);
	}
	return (0);
}

int main(void)
{
	int fd = open("text.txt",O_RDONLY);
	char *line;
	get_next_line(fd, &line);
	printf("%s\n",line);

	get_next_line(fd, &line);
	printf("%s\n",line);

	get_next_line(fd, &line);
	printf("%s\n",line);

	free(line);
	return (0);
}
